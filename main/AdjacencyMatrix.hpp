#pragma once
#include <vector>

using AdjacencyMatrix = std::vector<std::vector<bool>>;
using Vertex = size_t;
using Edge = std::pair<size_t, size_t>;

AdjacencyMatrix createAdjacencyMatrix(size_t n)
{
	return std::vector<std::vector<bool>>(n, std::vector<bool>(n, false));
}
