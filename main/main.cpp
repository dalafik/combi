#include "common/benchmark.hpp"
#include "common/stdext.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include "AdjacencyMatrix.hpp"
#include "FindMaximumFlow.hpp"

int main()
{
	size_t nVertices;
	std::cin >> nVertices;

	auto graph = createAdjacencyMatrix(nVertices);
	for (Vertex v = 0; v < nVertices; ++v)
	{
		for (Vertex u = 0; u < nVertices; ++u)
		{
			Weight w;
			std::cin >> w;
			graph[v][u] = w;
		}
	}

	const auto flow = FindMaximumFlow(graph);
	auto result = createAdjacencyMatrix(nVertices);
	for (const auto [v, u, w] : flow)
	{
		result[v][u] = w;
	}

	std::cout << nVertices << std::endl;
	for (Vertex v = 0; v < nVertices; ++v)
	{
		for (Vertex u = 0; u < nVertices; ++u)
		{
			std::cout << result[v][u] << ' ';
		}
		std::cout << std::endl;
	}

	return EXIT_SUCCESS;
}
