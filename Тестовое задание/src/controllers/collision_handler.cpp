#include "collision_handler.h"

#include <iostream>
#include <cmath>
#include "../utils/utils.h"
#include "../utils/record_serializator.h"

std::pair<Vect, Vect> CollisionHandler::collision_with_world(std::shared_ptr<Ball> ball,
	std::shared_ptr<World> world, std::shared_ptr<Score> score)
{
	std::pair<Vect, Vect> resault;

	Vect demo_world_size = world->get_world_size();

	float radius = ball->get_radius();

	// Сохранил реализацию расчета коллизии с миром из примера
	// Однако пофиксил использование magic number 2.0f
	if (ball->get_position().x < radius)
	{
		// Эта часть нарушает принцип единсвенной ответсвнности
		// Но сделал по предоставленному примеру
		ball->set_position(Vect(radius, ball->get_position().y));

		ball->set_velocity(Vect(ball->get_velocity().x * -1.0f, ball->get_velocity().y));

		resault.first = Vect(0, ball->get_position().y);
		resault.second = Vect(1, 0);

		return resault;
	}

	else if (ball->get_position().x > (demo_world_size.x - radius))
	{
		ball->set_position(Vect(demo_world_size.x - radius,
			ball->get_position().y));

		ball->set_velocity(Vect(ball->get_velocity().x * -1.0f, ball->get_velocity().y));

		resault.first = Vect(demo_world_size.x, ball->get_position().y);
		resault.second = Vect(-1, 0);

		return resault;
	}

	if (ball->get_position().y < radius)
	{
		ball->set_position(Vect(ball->get_position().x, radius));

		ball->set_velocity(Vect(ball->get_velocity().x, ball->get_velocity().y * -1.0f));

		resault.first = Vect(ball->get_position().x, 0);
		resault.second = Vect(0, 1);

		return resault;
	}
	else if (ball->get_position().y > (demo_world_size.y - radius))
	{
		std::cout << std::endl;
		std::cout << "You Lose!" << std::endl;
		std::cout << "Your score: " << score->get_current_score() << std::endl;
		if (score->get_current_score() > score->get_record_score()) {
			std::cout << "Its a new record!" << std::endl;
			std::cout << "Old record: " << score->get_record_score() << std::endl;
			RecordSerializator::serializeInt(score->get_current_score(), RecordSerializator::filename);
		}
		else {
			std::cout << "Record: " << score->get_record_score() << std::endl;
		}
		std::cout << "Please reset" << std::endl;
		std::cout << std::endl;

		ball->set_position(Vect(ball->get_position().x, demo_world_size.y - radius));

		ball->set_velocity(Vect(0, 0));
		ball->set_is_active(false);

		resault.first = Vect(ball->get_position().x, demo_world_size.y);
		resault.second = Vect(0, -1);

		return resault;
	}
	return std::make_pair(Vect(0, 0), Vect(0, 0));
}

std::pair<Vect, Vect> CollisionHandler::collision_with_briks(std::shared_ptr<Ball> ball,
	std::vector<Brick>& bricks, Vect& world_to_screen)
{
	std::pair<Vect, Vect> resault = std::make_pair(Vect(0, 0), Vect(0, 0));

	for (auto& brick : bricks)
	{
		if (brick.get_is_active()) {
			resault = collision_with_rect(ball, brick.get_position(),
				brick.get_height(), brick.get_width());
			if (!Utils::is_pair_zero(resault)) {
				brick.set_is_active(false);
				return resault;
			}
		}
	}
	return resault;
}

std::pair<Vect, Vect> CollisionHandler::collision_with_carriage(std::shared_ptr<Ball> ball,
	std::shared_ptr<Carriage> carriage, Vect& world_to_screen)
{
	return collision_with_rect(ball, carriage->get_position(),
		carriage->get_height(), carriage->get_width());
}

std::pair<Vect, Vect> CollisionHandler::collision_with_rect(std::shared_ptr<Ball> ball, Vect& pos, float height, float width)
{
	std::pair<Vect, Vect> resault;

	Vect ball_pos = ball->get_position();
	float radius = ball->get_radius();

	float closest_x = std::max(pos.x, std::min(ball_pos.x, pos.x + width));
	float closest_y = std::max(pos.y, std::min(ball_pos.y, pos.y + height));

	Vect to_closest = Vect(closest_x - ball_pos.x, closest_y - ball_pos.y);

	float length = Utils::length(to_closest);

	if (length <= radius) {

		to_closest.x /= length;
		to_closest.y /= length;

		Vect contac_ptoint = { ball_pos.x + radius * to_closest.x, ball_pos.y + radius * to_closest.y };
		Vect normal;

		if (to_closest.x > 0) {
			if (to_closest.y > 0) {
				if ((closest_x - ball_pos.x) > (closest_y - ball_pos.y)) {
					normal = { -1, 0 };
					if (ball->get_velocity().x > 0)
						// Тоже нарушает принцип единсвенной ответсвнности, но т.к. коллизия с миром уже	
						// Это делает, решил все сделать в одном стиле
						ball->set_velocity(Vect(ball->get_velocity().x * -1.0f, ball->get_velocity().y));
				}
				else {
					normal = { 0, -1 };
					if (ball->get_velocity().y > 0)
						ball->set_velocity(Vect(ball->get_velocity().x, ball->get_velocity().y * -1.0f));
				}
			}
			else {
				if ((closest_x - ball_pos.x) > (ball_pos.y - closest_y)) {
					normal = { -1, 0 };
					if (ball->get_velocity().x > 0)
						ball->set_velocity(Vect(ball->get_velocity().x * -1.0f, ball->get_velocity().y));
				}
				else {
					normal = { 0, 1 };
					if (ball->get_velocity().y < 0)
						ball->set_velocity(Vect(ball->get_velocity().x, ball->get_velocity().y * -1.0f));
				}
			}
		}
		else {
			if (to_closest.y > 0) {
				if ((ball_pos.x - closest_x) > (closest_y - ball_pos.y)) {
					normal = { 1, 0 };
					if (ball->get_velocity().x < 0)
						ball->set_velocity(Vect(ball->get_velocity().x * -1.0f, ball->get_velocity().y));
				}
				else {
					normal = { 0, -1 };
					if (ball->get_velocity().y > 0)
						ball->set_velocity(Vect(ball->get_velocity().x, ball->get_velocity().y * -1.0f));
				}
			}
			else {
				if ((ball_pos.x - closest_x) > (ball_pos.y - closest_y)) {
					normal = { 1, 0 };
					if (ball->get_velocity().x < 0)
						ball->set_velocity(Vect(ball->get_velocity().x * -1.0f, ball->get_velocity().y));
				}
				else {
					normal = { 0, 1 };
					if (ball->get_velocity().y < 0)
						ball->set_velocity(Vect(ball->get_velocity().x, ball->get_velocity().y * -1.0f));
				}
			}
		}

		resault.first = contac_ptoint;
		resault.second = normal;

		return resault;
	}
	return std::make_pair(Vect(0, 0), Vect(0, 0));
}
