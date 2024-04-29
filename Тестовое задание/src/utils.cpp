#include "utils.h"

bool Utils::is_pair_zero(std::pair<Vect, Vect>& pair)
{
	if (pair.first.x == 0.0f && pair.first.y == 0.0f && pair.second.x == 0.0f && pair.second.y == 0.0f) {
		return true;
	}
	return false;
}

float Utils::length(Vect vect)
{
	return sqrt(vect.x * vect.x + vect.y * vect.y);;
}
