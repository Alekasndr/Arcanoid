#pragma once

#include <vector>
#include "../models/brick.h"
#include "../models/world.h"
#include "../arkanoid.h"

class LevelGenerator
{
public:
	static std::vector<Brick> create_bricks_list(const ArkanoidSettings& settings);
	static void reset_bricks_list(std::vector<Brick>& briks, const ArkanoidSettings& settings);
};

