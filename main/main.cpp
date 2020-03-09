#include "common/benchmark.hpp"
#include "common/stdext.hpp"
#include "GenerateCombinations.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
	Benchmark([&]() {
		GenerateCombinations(5, 3, [](auto comb) {
			std::cout << comb << std::endl;
		});
	});

	return EXIT_SUCCESS;
}
