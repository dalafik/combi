#pragma once
#include <optional>
#include <set>
#include <algorithm>
#include <cassert>
#include "AdjacencyMatrix.hpp"

// Push–relabel maximum flow algorithm
// https://en.wikipedia.org/wiki/Push%E2%80%93relabel_maximum_flow_algorithm
// https://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%BF%D1%80%D0%BE%D1%82%D0%B0%D0%BB%D0%BA%D0%B8%D0%B2%D0%B0%D0%BD%D0%B8%D1%8F_%D0%BF%D1%80%D0%B5%D0%B4%D0%BF%D0%BE%D1%82%D0%BE%D0%BA%D0%B0

std::set<Edge> FindMaximumFlow(const AdjacencyMatrix& graph)
{
	const auto size = graph.size();
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

	const auto getOverflowedVertex = [&, source, sink]() -> std::optional<Vertex> {
		for (Vertex v = source; v < sink; ++v)
		{
			if (overflows[v] > 0)
			{
				return std::make_optional(v);
			}
		}
		return std::nullopt;
	};

	const auto push = [&, source, sink](Vertex v) -> bool {
		const size_t h = heights[v];
		for (Vertex u = source + 1; u < sink; ++u)
		{
			const Weight capacity = graph[v][u];
			const Weight remainingCapacity = capacity - flow[v][u];
			if (heights[u] < h && remainingCapacity > 0)
			{
				const Weight add = std::min(overflows[v], remainingCapacity);
				overflows[v] -= add;
				overflows[u] += add;
				flow[v][u] += add;
				return true;
			}
		}
		return false;
	};

	const auto lift = [&, source, sink](Vertex v) {
		constexpr size_t infinity = std::numeric_limits<size_t>::max();
		size_t min = infinity;
		for (Vertex u = source + 1; u < sink; ++u)
		{
			const Weight w = graph[v][u];
			if (w > 0)
			{
				assert(heights[u] >= heights[v]);
				min = std::min(min, heights[u]);
			}
		}
		assert(min != infinity);
		heights[v] = min + 1;
	};

	// Main loop
	while (const auto v = getOverflowedVertex())
	{
		if (!push(*v))
		{
			lift(*v);
		}
	}

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