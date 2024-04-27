#pragma once

#include "level_generator.h"
#include "../models/carriage.h"
#include "../models/ball.h"
#include "../models/brick.h"

class LevelController
{
public:
	LevelController(const ArkanoidSettings& settings);
	std::shared_ptr<std::vector<std::shared_ptr<Brick>>> get_bricks();
	std::shared_ptr <Carriage> get_carriage();
	std::shared_ptr <Ball> get_ball();
	void move_carriage(ImGuiIO& io);
	void reset(const ArkanoidSettings& settings);
private:
	void bricks_reset(const ArkanoidSettings& settings);
	std::shared_ptr<std::vector<std::shared_ptr<Brick>>> bricks;
	std::shared_ptr<World> world;
	std::shared_ptr<Carriage> carriage;
	std::shared_ptr<Ball> ball;
};

