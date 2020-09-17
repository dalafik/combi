#include <cassert>
#include <vector>
#include <boost/rational.hpp>

using Rational = boost::rational<int>;
using Matrix = std::vector<std::vector<Rational>>;

Rational FindDeterminant(const Matrix& originalMatrix);