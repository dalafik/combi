#pragma once
#include <optional>
#include <set>
#include <algorithm>
#include <cassert>
#include <functional>
#include "AdjacencyMatrix.hpp"

// Push�relabel maximum flow algorithm
// https://en.wikipedia.org/wiki/Push%E2%80%93relabel_maximum_flow_algorithm
// https://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%BF%D1%80%D0%BE%D1%82%D0%B0%D0%BB%D0%BA%D0%B8%D0%B2%D0%B0%D0%BD%D0%B8%D1%8F_%D0%BF%D1%80%D0%B5%D0%B4%D0%BF%D0%BE%D1%82%D0%BE%D0%BA%D0%B0

std::set<Edge> FindMaximumFlow(const AdjacencyMatrix& graph)
{
	const auto size = graph.size();
#ifdef _DEBUG
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
			overflows[source] += w;
		}
	}

	std::vector<size_t> heights(size, 0);
	heights[source] = size;

	const auto whileHasOverflowedVertex = [&, source, sink](const std::function<bool(Vertex v)>& callback) {
		std::vector<Vertex> overflowsOrder(size);
		for (Vertex v = source; v < size; ++v)
		{
			overflowsOrder[v] = v;
		}

		bool processed;
		do
		{
			processed = false;
			for (Vertex i = source; i < sink && !processed; ++i)
			{
				const Vertex v = overflowsOrder[i];
				if (overflows[v] > 0 && callback(v))
				{
					if (i != 0)
					{
						std::swap(overflowsOrder[i], overflowsOrder[0]);
					}
					processed = true;
				}
			}
		}
		while (processed);
	};

	const auto push = [&, source, sink, size](Vertex v) -> bool {
		const size_t h = heights[v];
		for (Vertex u = source + 1; u < size; ++u)
		{
			const Weight capacity = graph[v][u];
			const Weight usedCapacity = flow[v][u];
			const Weight remainingCapacity = capacity - usedCapacity;
			if (heights[u] < h && remainingCapacity != 0)
			{
				const Weight add = std::min(overflows[v], remainingCapacity);
				overflows[v] -= add;
				overflows[u] += add;
				flow[v][u] += add;
				flow[u][v] -= add;
#ifdef _DEBUG
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
		for (Vertex u = source + 1; u < size; ++u)
		{
			if (heights[u] < heights[v])
			{
				return false;
			}
			else if (graph[v][u] > 0)
			{
				min = std::min(min, heights[u]);
			}
		}
		heights[v] = min + 1;		
#ifdef _DEBUG
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