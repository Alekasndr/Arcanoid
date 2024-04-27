#pragma once

#include <memory>
#include <vector>
#include "../arkanoid.h"
#include "../models/ball.h"
#include "../models/world.h"
#include "../models/brick.h"
#include "../models/carriage.h"


class CollisionHandler
{
public:
	static void collision_with_world(std::shared_ptr<Ball> ball, std::shared_ptr<World> world,
		Vect& world_to_screen, ArkanoidDebugData& debug_data);
	static void collision_with_briks(std::shared_ptr<Ball> ball, std::shared_ptr<std::vector<std::shared_ptr<Brick>>> bricks,
		Vect& world_to_screen, ArkanoidDebugData& debug_data);
	static void collision_with_carriage(std::shared_ptr<Ball> ball, std::shared_ptr<Carriage> carriage,
		Vect& world_to_screen, ArkanoidDebugData& debug_data);
private:
	static void add_debug_hit(ArkanoidDebugData& debug_data, const Vect& pos, const Vect& normal, Vect& world_to_screen);
};

