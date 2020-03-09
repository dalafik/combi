#pragma once
#include <algorithm>
#include <boost/iterator/counting_iterator.hpp>
#include <functional>
#include <vector>

inline bool NextCombination(
	size_t n,
	size_t k,
	std::vector<size_t>& comb)
{
	for (size_t i = k - 1; i != static_cast<size_t>(-1); --i)
	{
		if (comb[i] < n - k + i)
		{
			++comb[i];
			for (size_t j = i + 1; j < k; ++j)
			{
				comb[j] = comb[j - 1] + 1;
			}
			return true;
		}
	}
	return false;
}

inline void GenerateCombinations(
	size_t n,
	size_t k,
	std::function<void(const std::vector<size_t>&)> callback)
{
	if (n == 0 || k == 0 || k > n)
	{
		return;
	}

	std::vector<size_t> comb = std::vector<size_t>(
		boost::counting_iterator<size_t>(0),
		boost::counting_iterator<size_t>(k));

	do
	{
		callback(comb);
	} while (NextCombination(n, k, comb));
}
