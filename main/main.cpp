#include "common/benchmark.hpp"
#include "common/stdext.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include "kPermutations.hpp"

// n == 10, k == 5, t == 0s
// n == 20, k == 5, t == 0.03s
// n == 50, k == 5, t == 3.2s
// n == 70, k == 5, t == 17.1s

int main()
{
	Benchmark([&]() {
		kPermutations(10, 5, [](auto& permut) {
			//std::cout << permut << std::endl;
		});
	});

	return EXIT_SUCCESS;
}
