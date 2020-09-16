#define CATCH_CONFIG_MAIN
#include <initializer_list>
#include "../main/FindStronglyConnectedComponents.hpp"
#include "catch.hpp"

std::set<std::set<Vertex>> components(std::initializer_list<std::set<Vertex>> list)
{
	return std::set<std::set<Vertex>>(list);
}

std::set<Vertex> vertices(std::initializer_list<Vertex> list)
{
	return std::set<Vertex>(list);
}

TEST_CASE("FindStronglyConnectedComponents")
{
	SECTION("empty")
	{
		const auto graph = createAdjacencyMatrixFromEdges(0, {});
		const auto sccs = FindStronglyConnectedComponents(graph);

		REQUIRE(sccs.empty());
	}

	SECTION("1, uni-directed edge")
	{
		const auto graph = createAdjacencyMatrixFromEdges(2, {
			{0, 1}
		});
		const auto sccs = FindStronglyConnectedComponents(graph);

		REQUIRE(sccs == components({
			vertices({ 0 }),
			vertices({ 1 }),
		}));
	}

	SECTION("1, bi-directed edge")
	{
		const auto graph = createAdjacencyMatrixFromEdges(2, {
			{0, 1},
			{1, 0},
		});
		const auto sccs = FindStronglyConnectedComponents(graph);

		REQUIRE(sccs == components({
			vertices({ 0, 1 }),
		}));
	}

	SECTION("2, uni-directed edges")
	{
		const auto graph = createAdjacencyMatrixFromEdges(3, {
			{0, 1},
			{1, 2},
		});
		const auto sccs = FindStronglyConnectedComponents(graph);

		REQUIRE(sccs == components({
			vertices({ 0 }),
			vertices({ 1 }),
			vertices({ 2 }),
		}));
	}

	SECTION("2, bi-directed edges")
	{
		const auto graph = createAdjacencyMatrixFromEdges(3, {
			{0, 1},
			{1, 0},
			{1, 2},
			{2, 1},
		});
		const auto sccs = FindStronglyConnectedComponents(graph);

		REQUIRE(sccs == components({
			vertices({ 0, 1, 2 }),
		}));
	}

	SECTION("one-way triangle")
	{
		const auto graph = createAdjacencyMatrixFromEdges(3, {
			{0, 1},
			{1, 2},
			{2, 0},
		});
		const auto sccs = FindStronglyConnectedComponents(graph);

		REQUIRE(sccs == components({
			vertices({ 0, 1, 2 }),
		}));
	}

	SECTION("2 separate, one-way triangles")
	{
		const auto graph = createAdjacencyMatrixFromEdges(6, {
			{0, 1},
			{1, 2},
			{2, 0},
			{3, 4},
			{4, 5},
			{5, 3},
		});
		const auto sccs = FindStronglyConnectedComponents(graph);

		REQUIRE(sccs == components({
			vertices({ 0, 1, 2 }),
			vertices({ 3, 4, 5 }),
		}));
	}

	SECTION("sample from https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm")
	{
		const auto graph = createAdjacencyMatrixFromEdges(8, {
			{ 0, 4 },
			{ 1, 0 },
			{ 1, 0 },
			{ 2, 1 },
			{ 2, 3 },
			{ 3, 2 },
			{ 4, 1 },
			{ 5, 1 },
			{ 5, 4 },
			{ 5, 6 },
			{ 6, 2 },
			{ 6, 5 },
			{ 7, 3 },
			{ 7, 6 },
			{ 7, 7 },
		});
		const auto sccs = FindStronglyConnectedComponents(graph);

		REQUIRE(sccs == components({
			vertices({ 0, 1, 4 }),
			vertices({ 2, 3 }),
			vertices({ 5, 6 }),
			vertices({ 7 }),
		}));
	}
}