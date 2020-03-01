#include "common/benchmark.hpp"
#include "common/stdext.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

// n = 5 with output, t = 0.85s
// n = 6 with output, t = 6.48s

// n = 10 without output, t = 0.04s
// n = 12 without output, t = 3.3s
// n = 13 without output, t = 44.0s

int main()
{
	//std::vector<int> permut = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	//std::vector<int> permut = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::vector<int> permut = { 0, 1, 2, 3, 4, 5, 6};
	std::sort(permut.begin(), permut.end());
	std::unique(permut.begin(), permut.end());

	benchmark([&]() {
		do
		{
			std::cout << permut << std::endl;
		} while (std::next_permutation(permut.begin(), permut.end()));
	});

	return EXIT_SUCCESS;
}
