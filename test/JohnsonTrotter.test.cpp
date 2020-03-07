#define CATCH_CONFIG_MAIN
#include "../main/JohnsonTrotter.hpp"
#include "catch.hpp"

TEST_CASE("JohnsonTrotter")
{
	std::vector<std::vector<size_t>> result, reference;
	const auto addToResult = [&](const std::vector<size_t>& permutation) {
		result.push_back(permutation);
	};

	SECTION("n == 0")
	{
		reference = {};
		JohnsonTrotter(0, addToResult);

		REQUIRE(reference == result);
	}

	SECTION("n == 1")
	{
		reference = {
			{ 0, },
		};
		JohnsonTrotter(1, addToResult);

		REQUIRE(reference == result);
	}

	SECTION("n == 2")
	{
		reference = {
			{ 0, 1, },
			{ 1, 0, },
		};
		JohnsonTrotter(2, addToResult);

		REQUIRE(reference == result);
	}

	SECTION("n == 3")
	{
		reference = {
			{ 0, 1, 2, },
			{ 0, 2, 1, },
			{ 2, 0, 1, },
			{ 2, 1, 0, },
			{ 1, 2, 0, },
			{ 1, 0, 2, },
		};
		JohnsonTrotter(3, addToResult);

		REQUIRE(reference == result);
	}
}