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

	/*
	SECTION("sample 1x1")
	{
		Matrix matrix = {
			{ 4 },
		};

		const Rational determinant = FindDeterminant(matrix);
		REQUIRE(determinant == 4);
	}

	SECTION("sample 2x2")
	{
		Matrix matrix = {
			{ 4, 6 },
			{ 3, 8 },
		};

		const Rational determinant = FindDeterminant(matrix);
		REQUIRE(determinant == 14);
	}

	SECTION("sample 3x3")
	{
		Matrix matrix = {
			{6, 1, 1},
			{4, -2, 5},
			{2, 8, 7},
		};

		const Rational determinant = FindDeterminant(matrix);
		REQUIRE(determinant == -306);
	}

	SECTION("sample 4x4")
	{
		Matrix matrix = {
			{ 4, 7, 2, 3 },
			{ 1, 3, 1, 2 },
			{ 2, 5, 3, 4 },
			{ 1, 4, 2, 3 },
		};

		const Rational determinant = FindDeterminant(matrix);
		REQUIRE(determinant == -3);
	}
*/
}