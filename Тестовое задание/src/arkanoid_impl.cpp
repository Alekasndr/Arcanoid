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
	if (level_controller.get() == nullptr) {
		level_controller = std::make_unique<LevelController>(settings);
	}
	else {
		level_controller.get()->reset(settings);
	}
}

void ArkanoidImpl::update(ImGuiIO& io, ArkanoidDebugData& debug_data, float elapsed)
{
	World* world = level_controller.get()->get_world().get();
	world->set_world_to_screen(Vect(io.DisplaySize.x / world->get_world_size().x,
		io.DisplaySize.y / world->get_world_size().y));

	level_controller.get()->move_carriage(io);

	level_controller.get()->update(debug_data, elapsed);
}

void ArkanoidImpl::draw(ImGuiIO& io, ImDrawList& draw_list)
{
	Vect world_to_screen = level_controller.get()->get_world().get()->get_world_to_screen();

	Ball* ball = level_controller.get()->get_ball().get();
	if (ball->get_is_active()) {
		draw_list.AddCircleFilled(ball->get_position() * world_to_screen,
			ball->get_radius() * world_to_screen.x, ImColor(100, 255, 100));
	}

	for (std::shared_ptr<Brick> brick : *level_controller.get()->get_bricks().get())
	{
		Brick* temp = brick.get();
		if (temp->get_is_active()) {
			draw_list.AddRectFilled(temp->get_position() * world_to_screen,
				Vect((temp->get_position().x + temp->get_width()) * world_to_screen.x,
					(temp->get_position().y + temp->get_height()) * world_to_screen.y),
				ImColor(255, 0, 0, 255));
		}
	}

	Carriage* carrige = level_controller.get()->get_carriage().get();
	draw_list.AddRectFilled(carrige->get_position() * world_to_screen,
		Vect((carrige->get_position().x + carrige->get_width()) * world_to_screen.x,
			(carrige->get_position().y + carrige->get_height()) * world_to_screen.y),
		ImColor(0, 0, 255, 255));
}

