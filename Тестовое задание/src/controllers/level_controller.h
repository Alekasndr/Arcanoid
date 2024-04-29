#pragma once

#include "level_generator.h"
#include "../models/carriage.h"
#include "../models/ball.h"
#include "../models/brick.h"
#include "../models/score.h"

class LevelController
{
public:
	LevelController(const ArkanoidSettings& settings);
	std::shared_ptr<std::vector<std::shared_ptr<Brick>>> get_bricks();
	std::shared_ptr<Carriage> get_carriage();
	std::shared_ptr<Ball> get_ball();
	std::shared_ptr<World> get_world();
	void move_carriage(ImGuiIO& io);
	void reset(const ArkanoidSettings& settings);
	void update(ArkanoidDebugData& debug_data, float elapsed);
private:
	void bricks_reset(const ArkanoidSettings& settings);
	void add_debug_hit(ArkanoidDebugData& debug_data, const Vect& pos, const Vect& normal, Vect& world_to_screen);
	void ball_move_with_carriage();
	std::shared_ptr<std::vector<std::shared_ptr<Brick>>> bricks;
	std::shared_ptr<World> world;
	std::shared_ptr<Carriage> carriage;
	std::shared_ptr<Ball> ball;
	std::shared_ptr<Score> score;
};

