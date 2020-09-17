#include "FindDeterminant.hpp"

Rational FindDeterminant(const Matrix& originalMatrix)
{
	const auto size = originalMatrix.size();
	assert(size > 0 && size == originalMatrix[0].size());

	Matrix matrix(originalMatrix);

	for (size_t row = 0; row < size; ++row)
	{
		const Rational divisor = matrix[row][row];
		if (divisor == 0)
		{
			return 0;
		}

		for (size_t r = row + 1; r < size; ++r)
		{
			const Rational coefficient = -matrix[r][row] / divisor;
			for (size_t col = row; col < size; ++col)
			{
				matrix[r][col] += matrix[row][col] * coefficient;
			}
		}
	}

	Rational determinant = 1;
	for (size_t i = 0; i < size; ++i)
	{
		determinant *= matrix[i][i];
	}

	return determinant;
}