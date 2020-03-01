#include <boost/timer/timer.hpp>
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

void Benchmark(
	std::function<void()> action,
	size_t repeats = 1)
{
	assert(action);
	assert(repeats > 0);

	boost::timer::cpu_timer timer;

	for (size_t i = 0; i < repeats; ++i)
	{
		timer.start();
		action();
		timer.stop();
		std::cout << "\nTimings:";
		std::cout << timer.format() << std::endl;
	}
}