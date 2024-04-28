#include "level_controller.h"
#include "input_controller.h"
#include "collision_handler.h"

#include <iostream>

LevelController::LevelController(const ArkanoidSettings& settings)
{
	this->world = std::make_shared<World>(settings.world_size);
	this->ball = std::make_shared<Ball>(Vect(100.0f, 100.0f), settings.ball_radius, settings.ball_speed);
	this->carriage = std::make_shared<Carriage>(Vect(301.0f, 300.0f), 50.0f);
	//this->bricks = LevelGenerator::create_bricks_list(settings);
}

std::shared_ptr<std::vector<std::shared_ptr<Brick>>> LevelController::get_bricks()
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

void LevelController::move_carriage(ImGuiIO& io)
{
	int direction = InputController::get_direction(io);
	Vect new_pos = Vect(carriage.get()->get_position().x + direction * carriage.get()->get_speed(),
		carriage.get()->get_position().y);

	if (new_pos.x > 0 && new_pos.x + carriage.get()->get_width() < world.get()->get_world_size().x) {
		carriage.get()->set_position(new_pos);
	}
}

void LevelController::reset(const ArkanoidSettings& settings)
{
	this->world.get()->reset(settings.world_size);
	this->ball.get()->reset(Vect(100.0f, 100.0f), settings.ball_radius, settings.ball_speed);
	this->carriage.get()->reset(Vect(301.0f, 300.0f), 50.0f);
	//bricks_reset(settings);
}

void LevelController::bricks_reset(const ArkanoidSettings& settings)
{
	// Тут работу с памятью еще лучше можно оптимизировать работу с памятью, с помощью пула
	// но тербует дополнительных затрат времени и избыточно для данного задания
	int size = bricks.get()->size();
	int new_size = settings.bricks_columns_count * settings.bricks_rows_count;

	if (size < new_size) {
		for (int i = 0; i < new_size - size; i++) {
			bricks.get()->push_back(std::make_shared<Brick>());
		}
	}
	else if (size > new_size) {
		for (int i = 0; i < size - new_size; i++) {
			bricks.get()->pop_back();
		}
	}

	LevelGenerator::reset_bricks_list(bricks, settings);
}

void LevelController::update(ArkanoidDebugData& debug_data, float elapsed)
{
	Vect passed_distance = ball->get_velocity() * elapsed;
	float range = sqrt(passed_distance.x * passed_distance.x + passed_distance.y * passed_distance.y);
	float radius = ball->get_radius();

	while (range > 0) {
		Vect current_velocity = ball->get_velocity();
		Vect current_direction = current_velocity / sqrt(current_velocity.x * current_velocity.x + current_velocity.y * current_velocity.y);
		if (range < radius) {
			ball->set_position(Vect(ball->get_position() + current_direction * (radius - range)));
		}
		else {
			ball->set_position(Vect(ball->get_position() + current_direction * radius));
		}

		std::pair<Vect, Vect> pair = CollisionHandler::collision_with_world(this->ball, this->world, this->world.get()->get_world_to_screen());

		if (check_pair(pair)) {
			add_debug_hit(debug_data, pair.first, pair.second, this->world.get()->get_world_to_screen());
		}

		pair = CollisionHandler::collision_with_carriage(this->ball, this->carriage, this->world.get()->get_world_to_screen());

		if (check_pair(pair)) {
			add_debug_hit(debug_data, pair.first, pair.second, this->world.get()->get_world_to_screen());
		}

		range -= radius;
	}



	/*
	pair = CollisionHandler::collision_with_briks(this->ball, this->bricks, this->world.get()->get_world_to_screen());

	if (check_pair(pair)) {
		add_debug_hit(debug_data, pair.first, pair.second, this->world.get()->get_world_to_screen());
	}
	*/
}

bool LevelController::check_pair(std::pair<Vect, Vect>& pair)
{
	if (pair.first.x == 0.0f && pair.first.y == 0.0f && pair.second.x == 0.0f && pair.second.y == 0.0f) {
		return false;
	}
	return true;
}

void LevelController::add_debug_hit(ArkanoidDebugData& debug_data, const Vect& pos, const Vect& normal, Vect& world_to_screen)
{
	ArkanoidDebugData::Hit hit;
	hit.screen_pos = pos * world_to_screen;
	hit.normal = normal;
	debug_data.hits.push_back(std::move(hit));
}
