#include <algorithm>
#include <boost/iterator/counting_iterator.hpp>
#include <functional>
#include <limits>
#include <optional>
#include <vector>

void JohnsonTrotter(
	int size,
	std::function<void(const std::vector<int>&)> callback)
{
	std::vector<int> permutation = std::vector<int>(
		boost::counting_iterator<int>(0),
		boost::counting_iterator<int>(size));
	std::vector<int> positions = permutation;
	std::vector<int> directions = std::vector<int>(size, -1);
	directions[0] = 0;

	callback(permutation);
	for (auto n = size - 1; n > 0; --n)
	{
		int currIndex = positions[n];
		int nextIndex = currIndex + directions[n];
		if (0 <= nextIndex && nextIndex < size && permutation[nextIndex] > n)
		{
			std::swap(permutation[currIndex], permutation[nextIndex]);
			std::swap(positions[currIndex], positions[nextIndex]);
			callback(permutation);
			direct = -direct;
		}
		else
		{
			directions[n] = -directions[n];
		}
	}
}