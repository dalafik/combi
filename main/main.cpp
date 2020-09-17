#include "common/benchmark.hpp"
#include "common/stdext.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include "AdjacencyMatrix.hpp"
#include "ColorGraph.hpp"

int main()
{
	size_t nVertices;
	size_t nEdges;
	std::vector<Edge> edges;

	std::cin >> nVertices >> nEdges;

	for (size_t i = 0; i < nEdges; ++i)
	{
		size_t v1, v2;
		std::cin >> v1 >> v2;
		edges.push_back(std::make_pair(v1 - 1, v2 - 1));
	}

	const auto graph = createAdjacencyMatrixFromEdges(nVertices, edges);
	const auto colors = ColorGraph(graph);

	for (Vertex v = 0; v < colors.size(); ++v)
	{
		std::cout << v + 1 << ' ' << colors[v] + 1 << std::endl;
	}

	return EXIT_SUCCESS;
}
