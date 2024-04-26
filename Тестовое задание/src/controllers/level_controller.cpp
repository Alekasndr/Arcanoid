#include "level_controller.h"
#include "input_controller.h"

#include <iostream>

LevelController::LevelController(const ArkanoidSettings& settings)
{
	this->world = std::make_shared<World>(settings.world_size);
	this->ball = std::make_shared<Ball>(Vect(0.0f, 0.0f), settings.ball_radius, settings.ball_speed);
	this->carriage = std::make_shared<Carriage>(Vect(world.get()->get_world_size().x / 2 - (settings.carriage_width / 2), settings.world_size.y - 20), settings.carriage_width);
	this->bricks = LevelGenerator::create_blocks_list(settings);
}

std::shared_ptr<std::vector<std::shared_ptr<Brick>>> LevelController::get_bricks()
{
	return bricks;
}

std::shared_ptr<Carriage> LevelController::get_carriage()
{
	return carriage;
}

void LevelController::move_carriage(ImGuiIO& io)
{
	int direction = InputController::get_dirrection(io);
	Vect new_pos = Vect(carriage.get()->get_position().x + direction * carriage.get()->get_speed(),
		carriage.get()->get_position().y);

	std::cout << new_pos.x + carriage.get()->get_width() << std::endl;

	if (new_pos.x > 0 && new_pos.x + carriage.get()->get_width() < world.get()->get_world_size().x) {
		carriage.get()->set_position(new_pos);
	}
}
