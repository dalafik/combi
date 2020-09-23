#pragma once
#include <vector>
#include <tuple>

using Weight = int;
using AdjacencyMatrix = std::vector<std::vector<Weight>>;
using Vertex = size_t;
using Edge = std::tuple<Vertex, Vertex, Weight>;

AdjacencyMatrix createAdjacencyMatrix(size_t n)
{
	return std::vector<std::vector<Weight>>(n, std::vector<Weight>(n, 0));
}

AdjacencyMatrix createAdjacencyMatrixFromEdges(size_t n, const std::vector<Edge>& edges)
{
	auto graph = createAdjacencyMatrix(n);

	for (const auto [v, u, w] : edges)
	{
		graph[v][u] = w;
	}

	return graph;
}
