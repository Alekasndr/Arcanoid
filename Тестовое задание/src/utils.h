#pragma once

#include <utility>
#include "base.h"

class Utils
{
public:
	static bool is_pair_zero(std::pair<Vect, Vect>& pair);
	static float length(Vect vect);
};

