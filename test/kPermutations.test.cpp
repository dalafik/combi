#define CATCH_CONFIG_MAIN
#include "../main/kPermutations.hpp"
#include "catch.hpp"

TEST_CASE("kPermutations")
{
	std::vector<std::vector<size_t>> result, reference;
	const auto addToResult = [&](const std::vector<size_t>& vec) {
		result.push_back(vec);
	};

	SECTION("n == 0, k == 0")
	{
		reference = {};
		kPermutations(0, 0, addToResult);

		REQUIRE(reference == result);
	}

	SECTION("n == 1, k == 1")
	{
		reference = {
			{0,},
		};
		kPermutations(1, 1, addToResult);

		REQUIRE(reference == result);
	}

	SECTION("n == 2, k == 1")
	{
		reference = {
			{0,},
			{1,},
		};
		kPermutations(2, 1, addToResult);

		REQUIRE(reference == result);
	}

	SECTION("n == 4, k == 3")
	{
		reference = {
			{ 0, 1, 2 },
			{ 0, 2, 1 },
			{ 1, 0, 2 },
			{ 1, 2, 0 },
			{ 2, 0, 1 },
			{ 2, 1, 0 },
			{ 0, 1, 3 },
			{ 0, 3, 1 },
			{ 1, 0, 3 },
			{ 1, 3, 0 },
			{ 3, 0, 1 },
			{ 3, 1, 0 },
			{ 0, 2, 3 },
			{ 0, 3, 2 },
			{ 2, 0, 3 },
			{ 2, 3, 0 },
			{ 3, 0, 2 },
			{ 3, 2, 0 },
			{ 1, 2, 3 },
			{ 1, 3, 2 },
			{ 2, 1, 3 },
			{ 2, 3, 1 },
			{ 3, 1, 2 },
			{ 3, 2, 1 }
		};
		kPermutations(4, 3, addToResult);

		REQUIRE(reference == result);
	}
}