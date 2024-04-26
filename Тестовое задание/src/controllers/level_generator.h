#pragma once

#include <vector>
#include "../models/brick.h"
#include "../models/world.h"
#include "../arkanoid.h"
#include "../base.h"

class LevelGenerator
{
public:
	static std::shared_ptr<std::vector<std::shared_ptr<Brick>>> create_blocks_list(const ArkanoidSettings& settings);
};

