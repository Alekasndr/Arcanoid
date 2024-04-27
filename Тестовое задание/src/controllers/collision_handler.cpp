#include "collision_handler.h"

#include <iostream>
#include <cmath>

void CollisionHandler::collision_with_world(std::shared_ptr<Ball> ball,
	std::shared_ptr<World> world, Vect& world_to_screen,
	ArkanoidDebugData& debug_data)
{
	Vect demo_world_size = world.get()->get_world_size();

	Ball* ball_p = ball.get();
	float radius = ball_p->get_radius();

	if (ball_p->get_position().x < radius)
	{
		std::cout << "1" << std::endl;
		ball_p->set_position(Vect(ball_p->get_position().x + (radius - ball_p->get_position().x) * 2.0f,
			ball_p->get_position().y));

		ball_p->set_velocity(Vect(ball_p->get_velocity().x * -1.0f, ball_p->get_velocity().y));

		add_debug_hit(debug_data, Vect(0, ball_p->get_position().y), Vect(1, 0), world_to_screen);
	}

	else if (ball_p->get_position().x > (demo_world_size.x - radius))
	{
		std::cout << "2" << std::endl;
		ball_p->set_position(Vect(ball_p->get_position().x -
			(ball_p->get_position().x - (demo_world_size.x - radius)) * 2.0f,
			ball_p->get_position().y));

		ball_p->set_velocity(Vect(ball_p->get_velocity().x * -1.0f, ball_p->get_velocity().y));

		add_debug_hit(debug_data, Vect(demo_world_size.x, ball_p->get_position().y), Vect(-1, 0), world_to_screen);
	}

	if (ball_p->get_position().y < radius)
	{
		std::cout << "3" << std::endl;
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
	ArkanoidDebugData& debug_data)
{
}

void CollisionHandler::collision_with_carriage(std::shared_ptr<Ball> ball,
	std::shared_ptr<Carriage> carriage, Vect& world_to_screen,
	ArkanoidDebugData& debug_data)
{
	Vect ball_pos = ball.get()->get_position();
	float radius = ball.get()->get_radius();

	Carriage* carriage_p = carriage.get();

	float closest_x = std::max(carriage_p->get_position().x, std::min(ball_pos.x, carriage_p->get_position().x + carriage_p->get_width()));
	float closest_y = std::max(carriage_p->get_position().y, std::min(ball_pos.y, carriage_p->get_position().y + carriage_p->get_height()));

	Vect to_closest = Vect(closest_x - ball_pos.x, closest_y - ball_pos.y);

	float lengthSquared = (to_closest.x * to_closest.x) + (to_closest.y * to_closest.y);

	if (lengthSquared <= radius * radius) {

		float length = sqrt(lengthSquared);
		to_closest.x /= length;
		to_closest.y /= length;

		// Находим точку контакта
		Vect contactPoint = Vect(ball_pos.x + radius * to_closest.x, ball_pos.y + radius * to_closest.y);

		Vect normal;
		if (to_closest.x > 0) {
			if (to_closest.y > 0) {
				if ((closest_x - ball_pos.x) > (closest_y - ball_pos.y)) {
					normal = { 1, 0 };
					ball->set_velocity(Vect(ball->get_velocity().x * -1.0f, ball->get_velocity().y));
				}
				else {
					normal = { 0, -1 };
					ball->set_velocity(Vect(ball->get_velocity().x, ball->get_velocity().y * -1.0f));
				}
			}
			else {
				if ((closest_x - ball_pos.x) > (ball_pos.y - closest_y)) {
					normal = { 1, 0 };
					ball->set_velocity(Vect(ball->get_velocity().x * -1.0f, ball->get_velocity().y));
				}
				else {
					normal = { 0, 1 };
					ball->set_velocity(Vect(ball->get_velocity().x * -1.0f, ball->get_velocity().y));
				}
			}
		}
		else {
			if (to_closest.y > 0) {
				if ((ball_pos.x - closest_x) > (closest_y - ball_pos.y)) {
					normal = { -1, 0 };
					ball->set_velocity(Vect(ball->get_velocity().x, ball->get_velocity().y * -1.0f));
				}
				else {
					normal = { 0, -1 };
					ball->set_velocity(Vect(ball->get_velocity().x, ball->get_velocity().y * -1.0f));
				}
			}
			else {
				if ((ball_pos.x - closest_x) > (ball_pos.y - closest_y)) {
					normal = { -1, 0 };
					ball->set_velocity(Vect(ball->get_velocity().x, ball->get_velocity().y * -1.0f));
				}
				else {
					normal = { 0, 1 };
					ball->set_velocity(Vect(ball->get_velocity().x * -1.0f, ball->get_velocity().y));
				}
			}
		}

		add_debug_hit(debug_data, contactPoint, normal, world_to_screen);
	}
}

void CollisionHandler::add_debug_hit(ArkanoidDebugData& debug_data, const Vect& pos, const Vect& normal, Vect& world_to_screen)
{
	ArkanoidDebugData::Hit hit;
	hit.screen_pos = pos * world_to_screen;
	hit.normal = normal;
	debug_data.hits.push_back(std::move(hit));
}
