#include "common/benchmark.hpp"
#include "common/stdext.hpp"
#include "JohnsonTrotter.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

// n = 10 without output, t = 0.51s
// n = 12 without output, t = 51.77s

// n = 50, 100 (estimation) t = ?

int main()
{
	Benchmark([&]() {
		JohnsonTrotter(12, [](auto permut) {
			// std::cout << permut << std::endl;
		});
	});

	return EXIT_SUCCESS;
}
