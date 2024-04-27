#include "collision_handler.h"

#include <iostream>
#include <cmath>

std::pair<Vect, Vect> CollisionHandler::collision_with_world(std::shared_ptr<Ball> ball,
	std::shared_ptr<World> world, Vect& world_to_screen)
{
	std::pair<Vect, Vect> resault;

	Vect demo_world_size = world.get()->get_world_size();

	Ball* ball_p = ball.get();
	float radius = ball_p->get_radius();

	if (ball_p->get_position().x < radius)
	{
		ball_p->set_position(Vect(ball_p->get_position().x + (radius - ball_p->get_position().x) * 2.0f,
			ball_p->get_position().y));

		ball_p->set_velocity(Vect(ball_p->get_velocity().x * -1.0f, ball_p->get_velocity().y));

		resault.first = Vect(0, ball_p->get_position().y);
		resault.second = Vect(1, 0);

		return resault;
	}

	else if (ball_p->get_position().x > (demo_world_size.x - radius))
	{
		ball_p->set_position(Vect(ball_p->get_position().x -
			(ball_p->get_position().x - (demo_world_size.x - radius)) * 2.0f,
			ball_p->get_position().y));

		ball_p->set_velocity(Vect(ball_p->get_velocity().x * -1.0f, ball_p->get_velocity().y));

		resault.first = Vect(demo_world_size.x, ball_p->get_position().y);
		resault.second = Vect(-1, 0);

		return resault;
	}

	if (ball_p->get_position().y < radius)
	{
		ball_p->set_position(Vect(ball_p->get_position().x,
			ball_p->get_position().y + (radius - ball_p->get_position().y) * 2.0f));

		ball_p->set_velocity(Vect(ball_p->get_velocity().x, ball_p->get_velocity().y * -1.0f));

		resault.first = Vect(ball_p->get_position().x, 0);
		resault.second = Vect(0, 1);

		return resault;
	}
	else if (ball_p->get_position().y > (demo_world_size.y - radius))
	{
		std::cout << "You Lose!" << std::endl;
		ball_p->set_position(Vect(ball_p->get_position().x,
			ball_p->get_position().y - (ball_p->get_position().y - (demo_world_size.y - radius)) * 2.0f));

		ball_p->set_velocity(Vect(ball_p->get_velocity().x, ball_p->get_velocity().y * -1.0f));

		resault.first = Vect(ball_p->get_position().x, demo_world_size.y);
		resault.second = Vect(0, -1);

		return resault;
	}
	return std::make_pair(Vect(0, 0), Vect(0, 0));
}

std::pair<Vect, Vect> CollisionHandler::collision_with_briks(std::shared_ptr<Ball> ball,
	std::shared_ptr<std::vector<std::shared_ptr<Brick>>> bricks, Vect& world_to_screen)
{
	std::pair<Vect, Vect> resault;
	for (std::shared_ptr<Brick> brick : *bricks.get())
	{
		Brick* temp = brick.get();
		resault = collision_with_rect(ball, temp->get_position(),
			temp->get_height(), temp->get_width());
	}
	return resault;
}

std::pair<Vect, Vect> CollisionHandler::collision_with_carriage(std::shared_ptr<Ball> ball,
	std::shared_ptr<Carriage> carriage, Vect& world_to_screen)
{
	return collision_with_rect(ball, carriage.get()->get_position(),
		carriage.get()->get_height(), carriage.get()->get_width());
}

std::pair<Vect, Vect> CollisionHandler::collision_with_rect(std::shared_ptr<Ball> ball, Vect& pos, float height, float width)
{
	std::pair<Vect, Vect> resault;

	Vect ball_pos = ball.get()->get_position();
	float radius = ball.get()->get_radius();

	float closest_x = std::max(pos.x, std::min(ball_pos.x, pos.x + width));
	float closest_y = std::max(pos.y, std::min(ball_pos.y, pos.y + height));

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

		resault.first = contactPoint;
		resault.second = normal;

		return resault;
	}
	return std::make_pair(Vect(0, 0), Vect(0, 0));
}
