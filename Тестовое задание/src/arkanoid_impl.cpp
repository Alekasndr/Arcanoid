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

	// TODO:
	// remove demo code
	demo_draw(io, draw_list);
}

void ArkanoidImpl::demo_draw(ImGuiIO& io, ImDrawList& draw_list)
{
	Vect demo_world_to_screen = level_controller.get()->get_world().get()->get_world_to_screen();
	Ball* ball = level_controller.get()->get_ball().get();

	Vect screen_pos = ball->get_position() * demo_world_to_screen;
	float screen_radius = ball->get_radius() * demo_world_to_screen.x;
	draw_list.AddCircleFilled(screen_pos, screen_radius, ImColor(100, 255, 100));


	/*
	for (std::shared_ptr<Brick> brick : *level_controller.get()->get_bricks().get())
	{
		Brick* temp = brick.get();
		draw_list.AddRectFilled(temp->get_position() * demo_world_to_screen,
			Vect((temp->get_position().x + temp->get_height()) * demo_world_to_screen.x,
				(temp->get_position().y + temp->get_width()) * demo_world_to_screen.y),
			ImColor(255, 0, 0, 255));
	}
	*/

	Carriage* carrige = level_controller.get()->get_carriage().get();
	draw_list.AddRectFilled(carrige->get_position() * demo_world_to_screen,
		Vect((carrige->get_position().x + carrige->get_width()) * demo_world_to_screen.x,
			(carrige->get_position().y + carrige->get_height()) * demo_world_to_screen.y),
		ImColor(0, 0, 255, 255));
}

