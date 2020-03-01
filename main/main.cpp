#include "common/benchmark.hpp"
#include "common/stdext.hpp"
#include "JohnsonTrotter.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
	Benchmark([&]() {
		JohnsonTrotter(6, [](auto permut) {
			std::cout << permut << std::endl;
		});
	});

	return EXIT_SUCCESS;
}
