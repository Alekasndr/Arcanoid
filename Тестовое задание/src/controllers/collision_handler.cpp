#include "collision_handler.h"

#include <iostream>

void CollisionHandler::collision_with_world(std::shared_ptr<Ball> ball,
	std::shared_ptr<World> world, Vect& world_to_screen,
	ArkanoidDebugData& debug_data, float elapsed)
{
	Vect demo_world_size = world.get()->get_world_size();

	Ball* ball_p = ball.get();
	float radius = ball_p->get_radius();

	ball_p->set_position(Vect(ball_p->get_position() + ball_p->get_velocity() * elapsed));


	if (ball_p->get_position().x < radius)
	{
		ball_p->set_position(Vect(ball_p->get_position().x + (radius - ball_p->get_position().x) * 2.0f,
			ball_p->get_position().y));

		ball_p->set_velocity(Vect(ball_p->get_velocity().x * -1.0f, ball_p->get_velocity().y));

		add_debug_hit(debug_data, Vect(0, ball_p->get_position().y), Vect(1, 0), world_to_screen);
	}

	else if (ball_p->get_position().x > (demo_world_size.x - radius))
	{
		ball_p->set_position(Vect(ball_p->get_position().x -
			(ball_p->get_position().x - (demo_world_size.x - radius)) * 2.0f,
			ball_p->get_position().y));

		ball_p->set_velocity(Vect(ball_p->get_velocity().x * -1.0f, ball_p->get_velocity().y));

		add_debug_hit(debug_data, Vect(demo_world_size.x, ball_p->get_position().y), Vect(-1, 0), world_to_screen);
	}

	if (ball_p->get_position().y < radius)
	{
		ball_p->set_position(Vect(ball_p->get_position().x,
			ball_p->get_position().y + (radius - ball_p->get_position().y) * 2.0f));

		ball_p->set_velocity(Vect(ball_p->get_velocity().x, ball_p->get_velocity().y * -1.0f));

		add_debug_hit(debug_data, Vect(ball_p->get_position().x, 0), Vect(0, 1), world_to_screen);
	}
	else if (ball_p->get_position().y > (demo_world_size.y - radius))
	{
		std::cout << "You Lose!" << std::endl;
		ball_p->set_position(Vect(ball_p->get_position().x,
			ball_p->get_position().y - (ball_p->get_position().y - (demo_world_size.y - radius)) * 2.0f));

		ball_p->set_velocity(Vect(ball_p->get_velocity().x, ball_p->get_velocity().y * -1.0f));

		add_debug_hit(debug_data, Vect(ball_p->get_position().x, demo_world_size.y), Vect(0, -1), world_to_screen);
	}
}

void CollisionHandler::collision_with_briks(std::shared_ptr<Ball> ball,
	std::shared_ptr<std::vector<std::shared_ptr<Brick>>> bricks, Vect& world_to_screen,
	ArkanoidDebugData& debug_data, float elapsed)
{
}

void CollisionHandler::collision_with_carriage(std::shared_ptr<Ball> ball,
	std::shared_ptr<Carriage> carriage, Vect& world_to_screen,
	ArkanoidDebugData& debug_data, float elapsed)
{
}

void CollisionHandler::add_debug_hit(ArkanoidDebugData& debug_data, const Vect& pos, const Vect& normal, Vect& world_to_screen)
{
	ArkanoidDebugData::Hit hit;
	hit.screen_pos = pos * world_to_screen;
	hit.normal = normal;
	debug_data.hits.push_back(std::move(hit));
}

