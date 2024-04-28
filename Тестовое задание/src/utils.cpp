#include "utils.h"

bool Utils::check_pair(std::pair<Vect, Vect>& pair)
{
	if (pair.first.x == 0.0f && pair.first.y == 0.0f && pair.second.x == 0.0f && pair.second.y == 0.0f) {
		return false;
	}
	return true;
}

float Utils::length(Vect vect)
{
	return sqrt(vect.x * vect.x + vect.y * vect.y);;
}
