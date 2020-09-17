#define CATCH_CONFIG_MAIN
#include <initializer_list>
#include "../main/ColorGraph.hpp"
#include "catch.hpp"

std::vector<Color> colors(std::initializer_list<Color> list)
{
	return std::vector<Color>(list);
}

bool invariant(const AdjacencyMatrix& graph, const std::vector<Color>& colors)
{
	for (Vertex v = 0; v < graph.size(); ++v)
	{
		for (Vertex u = 0; u < graph.size(); ++u)
		{
			if (v != u && graph[v][u] && colors[v] == colors[u])
			{
				return false;
			}
		}
	}

	return true;
}

TEST_CASE("ColorGraph")
{
	SECTION("empty")
	{
		const auto graph = createAdjacencyMatrixFromEdges(0, {});
		const auto result = ColorGraph(graph);

		REQUIRE(result.empty());
		REQUIRE(invariant(graph, result));
	}

	SECTION("1 vertex")
	{
		const auto graph = createAdjacencyMatrix(1);
		const auto result = ColorGraph(graph);

		REQUIRE(result == colors({ 0 }));
		REQUIRE(invariant(graph, result));
	}

	SECTION("2 vertices")
	{
		const auto graph = createAdjacencyMatrix(2);
		const auto result = ColorGraph(graph);

		REQUIRE(result == colors({ 0, 1 }));
		REQUIRE(invariant(graph, result));
	}

	SECTION("1 edge")
	{
		const auto graph = createAdjacencyMatrixFromEdges(2, {
			{0, 1}
		});
		const auto result = ColorGraph(graph);

		REQUIRE(result == colors({ 0, 1 }));
		REQUIRE(invariant(graph, result));
	}

	SECTION("2 connected edges")
	{
		const auto graph = createAdjacencyMatrixFromEdges(3, {
			{ 0, 1 },
			{ 1, 2 },
		});
		const auto result = ColorGraph(graph);

		REQUIRE(result == colors({ 0, 1, 0 }));
		REQUIRE(invariant(graph, result));
	}

	SECTION("triangle")
	{
		const auto graph = createAdjacencyMatrixFromEdges(3, {
			{ 0, 1 },
			{ 1, 2 },
			{ 2, 0 },
		});
		const auto result = ColorGraph(graph);

		REQUIRE(result == colors({ 0, 1, 2 }));
		REQUIRE(invariant(graph, result));
	}

	SECTION("Z-shaped")
	{
		const auto graph = createAdjacencyMatrixFromEdges(5, {
			{ 0, 1 },
			{ 1, 2 },
			{ 0, 3 },
			{ 3, 4 },
		});
		const auto result = ColorGraph(graph);

		REQUIRE(result == colors({ 0, 1, 0, 2, 0 }));
		REQUIRE(invariant(graph, result));
	}

	SECTION("example from lecture")
	{
		const auto graph = createAdjacencyMatrixFromEdges(9, {
			{ 0, 1 },
			{ 0, 2 },
			{ 0, 5 },
			{ 1, 3 },
			{ 1, 4 },			
			{ 1, 6 },
			{ 2, 3 },
			{ 2, 5 },
			{ 3, 4 },
			{ 3, 5 },
			{ 4, 5 },
			{ 4, 6 },
			{ 4, 8 },
			{ 5, 8 },
			{ 6, 8 },
			{ 7, 8 },
		});
		const auto result = ColorGraph(graph);

		REQUIRE(result == colors({ 0, 1, 2, 0, 3, 1, 0, 0, 4 }));
		REQUIRE(invariant(graph, result));
	}
}