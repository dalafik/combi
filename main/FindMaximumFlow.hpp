#pragma once
#include <optional>
#include <set>
#include <algorithm>
#include <cassert>
#include <functional>
#include "AdjacencyMatrix.hpp"

//#define TRACE

// Push–relabel maximum flow algorithm
// https://en.wikipedia.org/wiki/Push%E2%80%93relabel_maximum_flow_algorithm
// https://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%BF%D1%80%D0%BE%D1%82%D0%B0%D0%BB%D0%BA%D0%B8%D0%B2%D0%B0%D0%BD%D0%B8%D1%8F_%D0%BF%D1%80%D0%B5%D0%B4%D0%BF%D0%BE%D1%82%D0%BE%D0%BA%D0%B0

std::set<Edge> FindMaximumFlow(const AdjacencyMatrix& graph)
{
	const auto size = graph.size();
#ifdef TRACE
	printf("FindMaximumFlow(): size == %zi\n", size);
#endif
	if (size == 0)
	{
		return std::set<Edge>();
	}

	constexpr Vertex source = 0;
	const Vertex sink = size - 1;

	AdjacencyMatrix flow = createAdjacencyMatrix(size);
	std::vector<Weight> overflows(size);
	for (Vertex v = source + 1; v < size; ++v)
	{
		const Weight w = graph[source][v];
		if (w > 0)
		{
			flow[source][v] = w;
			flow[v][source] = -w;
			overflows[v] = w;
		}
	}

	std::vector<size_t> heights(size, 0);
	heights[source] = size;

	const auto whileHasOverflowedVertex = [&, source, sink](const std::function<bool(Vertex v)>& callback) {
		bool processed;
		do
		{
			processed = false;
			for (Vertex v = source + 1; v < sink && !processed; ++v)
			{
				processed = overflows[v] > 0 && callback(v);
			}
		}
		while (processed);
	};

	const auto getRemainingCapacity = [&](Vertex v, Vertex u) -> Weight {
		return graph[v][u] - flow[v][u];
	};

	const auto push = [&, source, size](Vertex v) -> bool {
		const size_t h = heights[v];
		for (Vertex u = source; u < size; ++u)
		{
			const Weight remainingCapacity = getRemainingCapacity(v, u);
			if (heights[u] < h && remainingCapacity != 0)
			{
				const Weight add = std::min(overflows[v], remainingCapacity);
				overflows[v] -= add;
				overflows[u] += add;
				flow[v][u] += add;
				flow[u][v] -= add;
#ifdef TRACE
				printf("pushed %i from %zi to %zi\n", add, v, u);
#endif
				return true;
			}
		}
		return false;
	};

	const auto lift = [&, source, size](Vertex v) -> bool {
		constexpr size_t infinity = std::numeric_limits<size_t>::max();
		size_t min = infinity;
		for (Vertex u = source; u < size; ++u)
		{
			if (getRemainingCapacity(v, u) != 0)
			{
				if (heights[v] > heights[u])
				{
					return false;
				}
				min = std::min(min, heights[u]);
			}
		}
		if (min == infinity)
		{
			return false;
		}
		heights[v] = min + 1;		
#ifdef TRACE
		printf("lifted %zi to %zi\n", v, heights[v]);
#endif
		return true;
	};

	// Main loop
	whileHasOverflowedVertex([&](Vertex v) {
		return push(v) || lift(v);
	});

	// Convert adjacency matrix to the set of edges
	std::set<Edge> result;
	for (Vertex v = source; v < sink; ++v)
	{
		for (Vertex u = source + 1; u < size; ++u)
		{
			const Weight w = flow[v][u];
			if (w > 0)
			{
				result.insert(std::make_tuple(v, u, w));
			}
		}
	}

	return result;
}