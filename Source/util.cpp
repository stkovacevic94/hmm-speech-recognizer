#include "util.h"

#include <cmath>

double sgn(double x)
{
	return x >= 0 ? 1 : -1;
}

double to_mel(double freq)
{
	return 1125 * log(1 + freq / 700);
}

double from_mel(double freq)
{
	return 700 * (exp(freq / 1125) - 1);
}