#include "level_controller.h"
#include "collision_handler.h"

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "../utils/utils.h"
#include "../utils/record_serializator.h"
#include <GLFW/glfw3.h>

LevelController::LevelController(const ArkanoidSettings& settings)
{
	world = std::make_shared<World>(settings.world_size);
	ball = std::make_shared<Ball>(Vect(settings.world_size.x / 2.0f, settings.world_size.y / 2.0f), settings.ball_radius, settings.ball_speed);
	carriage = std::make_shared<Carriage>(Vect(world.get()->get_world_size().x / 2.0f - (settings.carriage_width / 2.0f),
		settings.world_size.y - 20.0f), settings.carriage_width);
	bricks = LevelGenerator::create_bricks_list(settings);
	score = std::make_shared<Score>(RecordSerializator::deserializeInt(RecordSerializator::filename));
}

const std::vector<Brick>& LevelController::get_bricks() const
{
	return bricks;
}

std::shared_ptr<Carriage> LevelController::get_carriage()
{
	return carriage;
}

std::shared_ptr<Ball> LevelController::get_ball()
{
	return ball;
}

std::shared_ptr<World> LevelController::get_world()
{
	return world;
}

void LevelController::reset(const ArkanoidSettings& settings)
{
	world->reset(settings.world_size);
	ball->reset(Vect(settings.world_size.x / 2.0f, settings.world_size.y / 2.0f),
		settings.ball_radius, settings.ball_speed);
	carriage->reset(Vect(world->get_world_size().x / 2 - (settings.carriage_width / 2),
		settings.world_size.y - 20), settings.carriage_width);
	bricks_reset(settings);
	score->reset(RecordSerializator::deserializeInt(RecordSerializator::filename));
}

void LevelController::bricks_reset(const ArkanoidSettings& settings)
{
	//TODO: Тут работу с памятью еще лучше можно оптимизировать с помощью пула
	int size = bricks.size();
	int new_size = settings.bricks_columns_count * settings.bricks_rows_count;

	if (size < new_size) {
		for (int i = 0; i < new_size - size; i++) {
			bricks.emplace_back();
		}
	}
	else if (size > new_size) {
		for (int i = 0; i < size - new_size; i++) {
			bricks.pop_back();
		}
	}
	LevelGenerator::reset_bricks_list(bricks, settings);
}

void LevelController::update(ArkanoidDebugData& debug_data, float elapsed)
{
	Vect passed_distance = ball->get_velocity() * elapsed;
	float range = Utils::length(passed_distance);
	float radius = ball->get_radius();

	// Использовал алгоритм Ray Marching 
	// Для больших проектов лучше использовать алгоритм основанный на капсулях
	while (range > 0) {
		Vect current_velocity = ball->get_velocity();
		Vect current_direction = current_velocity / Utils::length(current_velocity);

		if (range < radius) {
			ball->set_position(Vect(ball->get_position() + current_direction * range));
		}
		else {
			ball->set_position(Vect(ball->get_position() + current_direction * radius));
		}
		range -= radius;

		std::pair<Vect, Vect> pair = CollisionHandler::collision_with_world(ball, world, score);

		if (!Utils::is_pair_zero(pair)) {
			add_debug_hit(debug_data, pair.first, pair.second, world->get_world_to_screen());
		}

		pair = CollisionHandler::collision_with_carriage(ball, carriage, world->get_world_to_screen());

		if (!Utils::is_pair_zero(pair)) {
			ball_move_with_carriage();
			add_debug_hit(debug_data, pair.first, pair.second, world->get_world_to_screen());
		}

		pair = CollisionHandler::collision_with_briks(ball, bricks, world->get_world_to_screen());

		if (!Utils::is_pair_zero(pair)) {
			score->set_current_score(score->get_current_score() + 1);
			std::cout << "Score: " << score->get_current_score() << std::endl;
			add_debug_hit(debug_data, pair.first, pair.second, world->get_world_to_screen());
		}
	}
}

void LevelController::ball_move_with_carriage()
{
	int direction = carriage->get_direction();
	if (direction != 0) {
		float movement_angle = atan2(ball->get_velocity().y, ball->get_velocity().x);
		float angle_barrier = M_PI / 6;
		float degree = M_PI / 180;
		float bias = 20.0f;

		if (movement_angle > M_PI - angle_barrier) {
			if (direction == 1) {
				movement_angle -= degree * bias;
			}
		}
		else if (movement_angle < angle_barrier) {
			if (direction == -1) {
				movement_angle += degree * bias;
			}
		}
		else {
			movement_angle += direction * degree * bias;
		}

		float length = Utils::length(ball->get_velocity());
		Vect norm_velocity = Vect(cos(movement_angle), sin(movement_angle));

		ball->set_velocity(Vect(norm_velocity.x * length, norm_velocity.y * length));

		std::cout << std::endl;
		std::cout << " x: " << ball->get_velocity().x << " y: " << ball->get_velocity().y << std::endl;
		std::cout << std::endl;

	}
}

void LevelController::add_debug_hit(ArkanoidDebugData& debug_data, const Vect& pos, const Vect& normal, Vect& world_to_screen)
{
	ArkanoidDebugData::Hit hit;
	hit.screen_pos = pos * world_to_screen;
	hit.normal = normal;
	debug_data.hits.push_back(std::move(hit));
}

void LevelController::move_carriage(ImGuiIO& io)
{
	if (io.KeysDown[GLFW_KEY_A])
		carriage->set_direction(-1.0f);
	else if (io.KeysDown[GLFW_KEY_D])
		carriage->set_direction(1.0f);
	else {
		carriage->set_direction(0);
	}

	Vect new_pos = Vect(carriage->get_position().x + carriage->get_direction() * carriage->get_speed(),
		carriage->get_position().y);

	if (new_pos.x > 0 && new_pos.x + carriage->get_width() < world->get_world_size().x) {
		carriage->set_position(new_pos);
	}
}