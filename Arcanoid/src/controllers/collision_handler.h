#pragma once

#include <memory>
#include <vector>
#include "../arkanoid.h"
#include "../models/ball.h"
#include "../models/world.h"
#include "../models/brick.h"
#include "../models/carriage.h"
#include "../models/score.h"

class CollisionHandler
{
public:
	static std::pair<Vect, Vect> collision_with_world(std::shared_ptr<Ball> ball, std::shared_ptr<World> world, std::shared_ptr<Score> score);
	static std::pair<Vect, Vect> collision_with_briks(std::shared_ptr<Ball> ball, std::vector<Brick>& bricks,
		Vect& world_to_screen);
	static std::pair<Vect, Vect> collision_with_carriage(std::shared_ptr<Ball> ball, std::shared_ptr<Carriage> carriage,
		Vect& world_to_screen);
private:
	static std::pair<Vect, Vect> collision_with_rect(std::shared_ptr<Ball> ball, Vect& pos, float height, float width);
};

