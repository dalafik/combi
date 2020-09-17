#pragma once
#include <set>
#include <functional>
#include <algorithm>
#include "AdjacencyMatrix.hpp"

// https://cp-algorithms.com/graph/cutpoints.html
// https://cp-algorithms.com/graph/bridge-searching.html
// https://www.hackerearth.com/ru/practice/algorithms/graphs/articulation-points-and-bridges/tutorial/

std::pair<std::set<Edge>, std::set<Vertex>>
FindBridgesAndArticulationPoints(const AdjacencyMatrix& graph)
{
	const auto nVertices = graph.size();
	std::set<Edge> bridges;
	std::set<Vertex> articulPoints;
	int timer = 0;
	std::vector<int> discovered(nVertices, -1);
	std::vector<int> lowestBack(nVertices, -1);

	std::function<void(Vertex, Vertex, int)> dfs = [&](
		Vertex vertex,
		Vertex parent,
		int time)
	{
		discovered[vertex] = lowestBack[vertex] = time;
		size_t nChildren = 0;

		for (size_t child = 0; child < nVertices; ++child)
		{
			if (!graph[vertex][child] || child == parent)
			{
				continue;
			}
			else if (discovered[child] != -1)
			{
				lowestBack[vertex] = std::min(lowestBack[vertex], discovered[child]);
			}
			else
			{
				++nChildren;
				dfs(child, vertex, timer++);
				lowestBack[vertex] = std::min(lowestBack[vertex], lowestBack[child]);
				if (lowestBack[child] >= discovered[vertex] && parent != -1)
				{
					articulPoints.insert(vertex);
				}
				if (lowestBack[child] > discovered[vertex])
				{
					bridges.insert(std::make_pair(vertex, child));
				}
			}
		}

		if (parent == -1 && nChildren > 1)
		{
			articulPoints.insert(vertex);
		}
	};

	for (size_t i = 0; i < nVertices; ++i)
	{
		if (discovered[i] == -1)
		{
			dfs(i, -1, timer++);
		}
	}

	return std::make_pair(bridges, articulPoints);
}