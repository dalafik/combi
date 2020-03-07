#pragma once
#include <algorithm>
#include <boost/iterator/counting_iterator.hpp>
#include <functional>
#include <vector>

inline void JohnsonTrotter(
	size_t size,
	std::function<void(const std::vector<size_t>&)> callback)
{
	if (size == 0)
	{
		return;	
	}

	std::vector<size_t> permutation = std::vector<size_t>(
		boost::counting_iterator<size_t>(0),
		boost::counting_iterator<size_t>(size));
	std::vector<size_t> positions = std::vector<size_t>(
		boost::counting_iterator<size_t>(0),
		boost::counting_iterator<size_t>(size));
	std::vector<int> directions = std::vector<int>(size, -1);
	directions[0] = 0;

	while (true)
	{
		size_t mobileElement = 0;
		size_t mobileIndex = 0;
		size_t adjacentElement = 0;
		size_t adjacentIndex = 0;

		callback(permutation);

		for (mobileElement = size - 1; mobileElement != 0; --mobileElement)
		{
			mobileIndex = positions[mobileElement];
			adjacentIndex = mobileIndex + directions[mobileElement];
			if (0 <= adjacentIndex && adjacentIndex < size)
			{
				adjacentElement = permutation[adjacentIndex];
				if (mobileElement > adjacentElement)
				{
					break;
				}
			}
			directions[mobileElement] = -directions[mobileElement];
		}
		if (mobileElement == 0)
		{
			break;
		}

		std::swap(permutation[mobileIndex], permutation[adjacentIndex]);
		std::swap(positions[mobileElement], positions[adjacentElement]);
	}
}
