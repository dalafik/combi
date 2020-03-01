#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <class T>
std::ostream&
operator<<(
	std::ostream& out,
	const std::vector<T>& v)
{
	out << '[';
	if (v.size() > 0)
	{
		std::copy(v.begin(), v.end() - 1, std::ostream_iterator<T>(out, ", "));
		out << v.back();
	}
	out << ']';
	return out;
}
