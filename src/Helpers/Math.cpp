#include "Helpers/Math.hpp"

void normalize(int& x, int& y) {
	int length = std::sqrt(x * x + y * y);
	if (length > 0)
	{
		x /= length;
		y /= length;
	}
}