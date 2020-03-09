#define CATCH_CONFIG_MAIN
#include "../main/GenerateCombinations.hpp"
#include "catch.hpp"

TEST_CASE("GenerateCombinations")
{
	std::vector<std::vector<size_t>> result, reference;
	const auto addToResult = [&](const std::vector<size_t>& vec) {
		result.push_back(vec);
	};

	SECTION("n == 0, k == 0")
	{
		reference = {};
		GenerateCombinations(0, 0, addToResult);

		REQUIRE(reference == result);
	}

	SECTION("n == 1, k == 1")
	{
		reference = {
			{ 0, },
		};
		GenerateCombinations(1, 1, addToResult);

		REQUIRE(reference == result);
	}

	SECTION("n == 2, k == 1")
	{
		reference = {
			{ 0, },
			{ 1, },
		};
		GenerateCombinations(2, 1, addToResult);

		REQUIRE(reference == result);
	}

	SECTION("n == 5, k == 3")
	{
		reference = {
			{ 0, 1, 2, },
			{ 0, 1, 3, },
			{ 0, 1, 4, },
			{ 0, 2, 3, },
			{ 0, 2, 4, },
			{ 0, 3, 4, },
			{ 1, 2, 3, },
			{ 1, 2, 4, },
			{ 1, 3, 4, },
			{ 2, 3, 4, },
		};
		GenerateCombinations(5, 3, addToResult);

		REQUIRE(reference == result);
	}
}