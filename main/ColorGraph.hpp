#pragma once
#include <cassert>
#include <set>
#include <functional>
#include <algorithm>
#include <optional>
#include "AdjacencyMatrix.hpp"

// https://cp-algorithms.com/graph/cutpoints.html
// https://cp-algorithms.com/graph/bridge-searching.html
// https://www.hackerearth.com/ru/practice/algorithms/graphs/articulation-points-and-bridges/tutorial/

using Color = int;
constexpr Color INVALID_COLOR = -1;

std::vector<Color>
ColorGraph(const AdjacencyMatrix& originalGraph)
{
	AdjacencyMatrix graph(originalGraph);
	const auto nVertices = graph.size();
	Color currentColor = INVALID_COLOR;
	std::vector<Color> colors(nVertices, INVALID_COLOR);
	std::vector<bool> collapsed(nVertices, false);
	constexpr int MAX_FIND_LEVEL = 2;

	const std::function<std::optional<Vertex>(size_t, Vertex, const std::function<bool(Vertex)>&)>
		findVertexRec = [&](
		size_t level,
		Vertex vertex,
		const std::function<bool(Vertex)>& predicate)
	{
		for (Vertex v = 0; v < nVertices; ++v)
		{
			if (graph[vertex][v]
				&& !collapsed[v]
				&& colors[v] == INVALID_COLOR
				&& predicate(v))
			{
				if (level == MAX_FIND_LEVEL)
				{
					return std::make_optional(v);
				}
				else if (const auto result = findVertexRec(level + 1, v, [&](Vertex v_) {
					return predicate(v_) && v != v_ && !graph[vertex][v_];
				}))
				{
					return result;
				}
			}
		}

		return static_cast<std::optional<Vertex>>(std::nullopt);
	};

	const auto collapse = [&](Vertex src, Vertex dst) {
		assert(src != dst);

		for (Vertex v = 0; v < nVertices; ++v)
		{
			if (v != dst)
			{
				graph[dst][v] = graph[dst][v] || graph[src][v];
				graph[v][dst] = graph[v][dst] || graph[v][src];
			}
		}

		collapsed[src] = true;
	};

	for (size_t v = 0; v < nVertices; ++v)
	{
		if (colors[v] != INVALID_COLOR)
		{
			continue;
		}

		++currentColor;
		colors[v] = currentColor;
		while (const auto v2 = findVertexRec(1, v, [&](Vertex v_) {
			return v != v_;
		}))
		{
			colors[*v2] = currentColor;
			collapse(*v2, v);
		}
	}

	return colors;
}