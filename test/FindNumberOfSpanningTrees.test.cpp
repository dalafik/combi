#define CATCH_CONFIG_MAIN
#include <initializer_list>
#include "../main/FindNumberOfSpanningTrees.hpp"
#include "catch.hpp"

TEST_CASE("FindNumberOfSpanningTrees")
{
	SECTION("1 vertex")
	{
		const auto graph = createAdjacencyMatrix(1);
		const auto result = FindNumberOfSpanningTrees(graph);

		REQUIRE(result == 1);
	}

	SECTION("1 edge")
	{
		const auto graph = createAdjacencyMatrixFromEdges(2, {
			{0, 1}
		});
		const auto result = FindNumberOfSpanningTrees(graph);

		REQUIRE(result == 1);
	}

	SECTION("2 connected edges")
	{
		const auto graph = createAdjacencyMatrixFromEdges(3, {
			{ 0, 1 },
			{ 1, 2 },
		});
		const auto result = FindNumberOfSpanningTrees(graph);

		REQUIRE(result == 1);
	}

	SECTION("triangle")
	{
		const auto graph = createAdjacencyMatrixFromEdges(3, {
			{ 0, 1 },
			{ 1, 2 },
			{ 2, 0 },
		});
		const auto result = FindNumberOfSpanningTrees(graph);

		REQUIRE(result == 3);
	}

	SECTION("4 edges")
	{
		const auto graph = createAdjacencyMatrixFromEdges(4, {
			{ 0, 1 },
			{ 0, 2 },
			{ 1, 2 },
			{ 2, 3 },
		});
		const auto result = FindNumberOfSpanningTrees(graph);

		REQUIRE(result == 3);
	}

	SECTION("4 vertex full graph")
	{
		const auto graph = createAdjacencyMatrixFromEdges(4, {
			{ 0, 1 },
			{ 0, 2 },
			{ 0, 3 },
			{ 1, 3 },
			{ 2, 1 },
			{ 2, 3 },
		});
		const auto result = FindNumberOfSpanningTrees(graph);

		REQUIRE(result == 16);
	}
}