#define CATCH_CONFIG_MAIN
#include <initializer_list>
#include "../main/FindBridgesAndArticulationPoints.hpp"
#include "catch.hpp"

std::set<Vertex> vertices(std::initializer_list<Vertex> list)
{
	return std::set<Vertex>(list);
}

std::set<Edge> edges(std::initializer_list<Edge> list)
{
	return std::set<Edge>(list);
}

TEST_CASE("FindBridgesAndArticulationPoints")
{
	SECTION("empty")
	{
		const auto graph = createAdjacencyMatrixFromEdges(0, {});
		const auto [bridges, points] = FindBridgesAndArticulationPoints(graph);

		REQUIRE(bridges.empty());
		REQUIRE(points.empty());
	}

	SECTION("single edge")
	{
		const auto graph = createAdjacencyMatrixFromEdges(2, {
			{0, 1}
		});
		const auto [bridges, points] = FindBridgesAndArticulationPoints(graph);

		REQUIRE(bridges == edges({ {0, 1} }));
		REQUIRE(points.empty());	
	}

	SECTION("2 connected edges")
	{
		const auto graph = createAdjacencyMatrixFromEdges(3, {
			{ 0, 1 },
			{ 1, 2 },
		});
		const auto [bridges, points] = FindBridgesAndArticulationPoints(graph);

		REQUIRE(bridges == edges({ { 0, 1 }, { 1, 2 } }));
		REQUIRE(points == vertices({ 1 }));
	}

	SECTION("triangle")
	{
		const auto graph = createAdjacencyMatrixFromEdges(3, {
			{ 0, 1 },
			{ 1, 2 },
			{ 2, 0 },
		});
		const auto [bridges, points] = FindBridgesAndArticulationPoints(graph);

		REQUIRE(bridges.empty());
		REQUIRE(points.empty());
	}

	SECTION("2 triangles connected by 1 bridge")
	{
		const auto graph = createAdjacencyMatrixFromEdges(6, {
			{ 0, 1 },
			{ 1, 2 },
			{ 2, 0 },

			{ 3, 4 },
			{ 4, 5 },
			{ 5, 3 },

			{ 0, 3 },
		});
		const auto [bridges, points] = FindBridgesAndArticulationPoints(graph);

		REQUIRE(bridges == edges({ { 0, 3 } }));
		REQUIRE(points == vertices({ 0, 3 }));
	}

	SECTION("sample from https://www.hackerearth.com/ru/practice/algorithms/graphs/articulation-points-and-bridges/tutorial/")
	{
		const auto graph = createAdjacencyMatrixFromEdges(6, {
			{ 0, 5 },
			{ 0, 1 },
			{ 1, 2 },
			{ 1, 3 },
			{ 2, 3 },
			{ 2, 4 },
			{ 3, 4 },
		});
		const auto [bridges, points] = FindBridgesAndArticulationPoints(graph);

		REQUIRE(bridges == edges({ { 0, 1 }, { 0, 5 } }));
		REQUIRE(points == vertices({ 0, 1 }));
	}

}