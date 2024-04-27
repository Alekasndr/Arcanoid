#include "level_controller.h"
#include "input_controller.h"
#include "collision_handler.h"

#include <iostream>

LevelController::LevelController(const ArkanoidSettings& settings)
{
	this->world = std::make_shared<World>(settings.world_size);
	this->ball = std::make_shared<Ball>(Vect(settings.world_size.x / 2.0f, settings.world_size.y / 2.0f), settings.ball_radius, settings.ball_speed);
	this->carriage = std::make_shared<Carriage>(Vect(world.get()->get_world_size().x / 2.0f - (settings.carriage_width / 2.0f), settings.world_size.y - 20.0f), settings.carriage_width);
	this->bricks = LevelGenerator::create_bricks_list(settings);
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
	this->ball.get()->reset(Vect(0.0f, 0.0f), settings.ball_radius, settings.ball_speed);
	this->carriage.get()->reset(Vect(world.get()->get_world_size().x / 2 - (settings.carriage_width / 2), settings.world_size.y - 20), settings.carriage_width);
	bricks_reset(settings);
}

void LevelController::bricks_reset(const ArkanoidSettings& settings)
{
	// ��� ������ � ������� ��� ����� ����� �������������� ������ � �������, � ������� ����
	// �� ������� �������������� ������ ������� � ��������� ��� ������� �������
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
	CollisionHandler::collision_with_world(this->ball, this->world, this->world.get()->get_world_to_screen(),
		debug_data, elapsed);
}
