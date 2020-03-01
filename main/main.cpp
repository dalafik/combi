#include "common/benchmark.hpp"
#include "common/stdext.hpp"
#include "CJohnsonTrotter.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
	std::vector<int> permut = { 7, 1, 12, 5, 9, 20, 15 };

	Benchmark([&]() {
		CJohnsonTrotter algo(permut);
		do
		{
			std::cout << permut << std::endl;
		} while (std::next_permutation(permut.begin(), permut.end()));
	});

	return EXIT_SUCCESS;
}
