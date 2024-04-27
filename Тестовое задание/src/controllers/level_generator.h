#pragma once

#include <vector>
#include "../models/brick.h"
#include "../models/world.h"
#include "../arkanoid.h"

class LevelGenerator
{
public:
	static std::shared_ptr<std::vector<std::shared_ptr<Brick>>> create_bricks_list(const ArkanoidSettings& settings);
	static void reset_bricks_list(std::shared_ptr<std::vector<std::shared_ptr<Brick>>> briks, const ArkanoidSettings& settings);
};

