#pragma once
#include <set>
#include <functional>
#include <algorithm>
#include <stack>
#include "AdjacencyMatrix.hpp"

// https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm

std::set<std::set<Vertex>>
FindStronglyConnectedComponents(const AdjacencyMatrix& graph)
{
	const auto nVertices = graph.size();
	int timer = 0;
	std::vector<int> discovered(nVertices, -1);
	std::vector<int> lowestBack(nVertices, -1);
	std::stack<Vertex> stack;
	std::vector<bool> onStack(nVertices, false);
	std::set<std::set<Vertex>> sccs;

	std::function<void(Vertex, int)> dfs = [&](
		Vertex vertex,
		int time)
	{
		discovered[vertex] = lowestBack[vertex] = time;
		stack.push(vertex);
		onStack[vertex] = true;

		for (size_t child = 0; child < nVertices; ++child)
		{
			if (!graph[vertex][child])
			{
				continue;
			}
			else if (discovered[child] == -1)
			{
				dfs(child, timer++);
				lowestBack[vertex] = std::min(lowestBack[vertex], lowestBack[child]);
			}
			else if (onStack[child])
			{
				
				lowestBack[vertex] = std::min(lowestBack[vertex], discovered[child]);
			}
		}

		if (lowestBack[vertex] == discovered[vertex])
		{
			std::set<Vertex> scc;
			Vertex v;

			do
			{
				v = stack.top();
				stack.pop();
				onStack[v] = false;
				scc.insert(v);
			}
			while (!stack.empty() && v != vertex);

			sccs.insert(scc);
		}
	};

	for (size_t i = 0; i < nVertices; ++i)
	{
		if (discovered[i] == -1)
		{
			dfs(i, timer++);
		}
	}

	return sccs;
}