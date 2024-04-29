#include "arkanoid_impl.h"

#include <GLFW/glfw3.h>

#ifdef USE_ARKANOID_IMPL
Arkanoid* create_arkanoid()
{
	return new ArkanoidImpl();
}
#endif

void ArkanoidImpl::reset(const ArkanoidSettings& settings)
{
	if (level_controller == nullptr) {
		level_controller = std::make_unique<LevelController>(settings);
	}
	else {
		level_controller->reset(settings);
	}
}

void ArkanoidImpl::update(ImGuiIO& io, ArkanoidDebugData& debug_data, float elapsed)
{
	auto world = level_controller->get_world();
	world->set_world_to_screen(Vect(io.DisplaySize.x / world->get_world_size().x,
		io.DisplaySize.y / world->get_world_size().y));

	level_controller->move_carriage(io);

	level_controller->update(debug_data, elapsed);
}

void ArkanoidImpl::draw(ImGuiIO& io, ImDrawList& draw_list)
{
	Vect world_to_screen = level_controller->get_world()->get_world_to_screen();

	auto ball = level_controller->get_ball();
	if (ball->get_is_active()) {
		draw_list.AddCircleFilled(ball->get_position() * world_to_screen,
			ball->get_radius() * world_to_screen.x, ImColor(100, 255, 100));
	}

	for (auto& brick : level_controller->get_bricks())
	{
		if (brick.get_is_active()) {
			draw_list.AddRectFilled(brick.get_position() * world_to_screen,
				Vect((brick.get_position().x + brick.get_width()) * world_to_screen.x,
					(brick.get_position().y + brick.get_height()) * world_to_screen.y),
				ImColor(255, 0, 0, 255));
		}
	}

	auto carrige = level_controller->get_carriage();
	draw_list.AddRectFilled(carrige->get_position() * world_to_screen,
		Vect((carrige->get_position().x + carrige->get_width()) * world_to_screen.x,
			(carrige->get_position().y + carrige->get_height()) * world_to_screen.y),
		ImColor(0, 0, 255, 255));
}

