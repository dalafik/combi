#pragma once
#include <iostream>
#include <numeric>
#include "AdjacencyMatrix.hpp"
#include "FindDeterminant.hpp"

Matrix GetKirchhoffMatrix(const AdjacencyMatrix& graph)
{
	const auto size = graph.size();
	const auto getDegree = [&](Vertex vertex) {
		const auto& row = graph[vertex];
		return std::reduce(row.begin(), row.end(), 0, [](int degree, bool hasEdge) {
			return hasEdge
				? degree + 1
				: degree;
		});
	};

	Matrix matrix(size, std::vector<Rational>(size));
	for (size_t row = 0; row < size; ++row)
	{
		for (size_t col = 0; col < size; ++col)
		{
			if (row == col)
			{
				matrix[row][row] = getDegree(row);
			}
			else if (graph[row][col])
			{
				matrix[row][col] = -1;
			}
			else
			{
				matrix[row][col] = 0;
			}
		}
	}

	return matrix;
}

int GetKirchhoffMinor(Matrix& matrix)
{
	matrix.pop_back();
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		matrix[i].pop_back();
	}

	return boost::rational_cast<int>(FindDeterminant(matrix));
}

int FindNumberOfSpanningTrees(const AdjacencyMatrix& graph)
{
	if (graph.size() == 0 || graph.size() == 1)
	{
		return static_cast<int>(graph.size());
	}

	Matrix matrix = GetKirchhoffMatrix(graph);
	const auto minor = GetKirchhoffMinor(matrix);
	const auto cofactor = (matrix.size() * 2) & 0x1
		? -minor
		: minor;
	return cofactor;
}