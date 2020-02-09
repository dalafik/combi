#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

template<class T>
std::ostream&
operator <<(
	std::ostream& out,
	const std::vector<T>& v)
{
	out << '[';
	std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
	out << ']';
	return out;
}
