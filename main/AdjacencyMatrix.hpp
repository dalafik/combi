#pragma once
#include <vector>

using AdjacencyMatrix = std::vector<std::vector<bool>>;
using Vertex = size_t;
using Edge = std::pair<Vertex, Vertex>;

AdjacencyMatrix createAdjacencyMatrix(size_t n)
{
	return std::vector<std::vector<bool>>(n, std::vector<bool>(n, false));
}

AdjacencyMatrix createAdjacencyMatrixFromEdges(size_t n, const std::vector<Edge>& edges)
{
	auto graph = createAdjacencyMatrix(n);

	for (const auto [v, u] : edges)
	{
		graph[v][u] = true;
	}

	return graph;
}
