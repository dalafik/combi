#define CATCH_CONFIG_MAIN
#include <initializer_list>
#include "../main/FindMaximumFlow.hpp"
#include "catch.hpp"

std::set<Edge> edges(std::initializer_list<Edge> list)
{
	return std::set<Edge>(list);
}

TEST_CASE("FindMaximumFlow")
{
	SECTION("empty")
	{
		const auto graph = createAdjacencyMatrixFromEdges(0, {});
		const auto result = FindMaximumFlow(graph);

		REQUIRE(result.empty());
	}

	SECTION("single edge")
	{
		const auto graph = createAdjacencyMatrixFromEdges(2, {
			{0, 1, 100}
		});
		const auto result = FindMaximumFlow(graph);

		REQUIRE(result == edges({ { 0, 1, 100 } }));
	}

	SECTION("2 connected edges, 1st < 2nd")
	{
		const auto graph = createAdjacencyMatrixFromEdges(3, {
			{ 0, 1, 50 },
			{ 1, 2, 100 },
		});
		const auto result = FindMaximumFlow(graph);

		REQUIRE(result == edges({ 
			{ 0, 1, 50 },
			{ 1, 2, 50 },
		}));
	}

	SECTION("2 connected edges, 1st > 2nd")
	{
		const auto graph = createAdjacencyMatrixFromEdges(3, {
			{ 0, 1, 100 },
			{ 1, 2, 50 },
		});
		const auto result = FindMaximumFlow(graph);

		REQUIRE(result == edges({ 
			{ 0, 1, 50 },
			{ 1, 2, 50 },
		}));
	}

	SECTION("triangle #1")
	{
		const auto graph = createAdjacencyMatrixFromEdges(3, {
			{ 0, 1, 50 },
			{ 1, 2, 50 },
			{ 0, 2, 50 }
		});
		const auto result = FindMaximumFlow(graph);

		REQUIRE(result == edges({ 
			{ 0, 1, 50 },
			{ 1, 2, 50 },
			{ 0, 2, 50 }
		}));
	}

	SECTION("triangle #2")
	{
		const auto graph = createAdjacencyMatrixFromEdges(3, {
			{ 0, 1, 50 },
			{ 1, 2, 50 },
			{ 2, 0, 50 }
		});
		const auto result = FindMaximumFlow(graph);

		REQUIRE(result == edges({ 
			{ 0, 1, 50 },
			{ 1, 2, 50 },
		}));
	}

	SECTION("triangle #2")
	{
		const auto graph = createAdjacencyMatrixFromEdges(3, {
			{ 0, 1, 50 },
			{ 1, 2, 50 },
			{ 2, 0, 50 }
		});
		const auto result = FindMaximumFlow(graph);

		REQUIRE(result == edges({ 
			{ 0, 1, 50 },
			{ 1, 2, 50 },
		}));
	}

	SECTION("dead end")
	{
		const auto graph = createAdjacencyMatrixFromEdges(5, {
			{ 0, 1, 100 },
			{ 1, 2, 50 },
			{ 0, 3, 50 },
			{ 3, 4, 100 },
		});
		const auto result = FindMaximumFlow(graph);

		REQUIRE(result == edges({ 
			{ 0, 3, 50 },
			{ 3, 4, 50 },
		}));
	}

	SECTION("example https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/")
	{
		const auto graph = createAdjacencyMatrixFromEdges(6, {
			{ 0, 1, 16 },
			{ 0, 2, 13 },
			{ 1, 2, 10 },
			{ 1, 3, 12 },
			{ 2, 1, 4 },
			{ 2, 4, 14 },
			{ 3, 2, 9 },
			{ 3, 5, 20 },
			{ 4, 3, 7 },
			{ 4, 5, 4 },
		});
		const auto result = FindMaximumFlow(graph);

		REQUIRE(result == edges({ 
			{ 0, 1, 13 },
			{ 0, 2, 10 },
			{ 1, 2, 1 },
			{ 1, 3, 12 },
			{ 2, 4, 11 },
			{ 3, 5, 19 },
			{ 4, 3, 7 },
			{ 4, 5, 4 },
		}));
	}
}