#pragma once
#include <vector>
#include <functional>

void JohnsonTrotter(
	size_t size,
	std::function<void(const std::vector<size_t>&)> callback
);