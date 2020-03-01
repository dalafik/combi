#include "common/benchmark.hpp"
#include "common/stdext.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

void Shuffle(
	std::vector<int>& vec)
{
	for (int& elem : vec)
	{
		int i = std::rand() % vec.size();
		std::swap(elem, vec[i]);
	}
}

int main()
{
	std::vector<int> permut = { 0, 1, 2, 3, 4, 5, 6 };

	std::srand(std::time(nullptr));

	benchmark([&]() {
		std::cout << "Before: " << permut << std::endl;
		Shuffle(permut);
		std::cout << "After: " << permut << std::endl;
	});

	return EXIT_SUCCESS;
}
