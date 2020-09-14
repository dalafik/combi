#pragma once
#include <functional>
#include "GenerateCombinations.hpp"

void kPermutations(
	size_t n,
	size_t k,
	std::function<void(const std::vector<size_t>&)> callback)
{
	GenerateCombinations(n, k, [&callback](const std::vector<size_t>& combination) {
		std::vector<size_t> permutation = combination;
		do
		{
			callback(permutation);
		} while (std::next_permutation(permutation.begin(), permutation.end()));
	});
}