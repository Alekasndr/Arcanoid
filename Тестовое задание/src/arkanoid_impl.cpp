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


	// TODO:
	// remove demo code
	demo_update(io, debug_data, elapsed);
}

void ArkanoidImpl::draw(ImGuiIO& io, ImDrawList& draw_list)
{
	// TODO:
	// Implement you Arkanoid drawing
	// ...

	// TODO:
	// remove demo code
	demo_draw(io, draw_list);
}

void ArkanoidImpl::demo_update(ImGuiIO& io, ArkanoidDebugData& debug_data, float elapsed)
{
	// update ball position according
	// its velocity and elapsed time

	Vect demo_world_size = level_controller.get()->get_world().get()->get_world_size();

	Ball* ball = level_controller.get()->get_ball().get();
	float radius = ball->get_radius();

	ball->set_position(Vect(ball->get_position() + ball->get_velocity() * elapsed));


	if (ball->get_position().x < radius)
	{
		ball->set_position(Vect(ball->get_position().x + (radius - ball->get_position().x) * 2.0f,
			ball->get_position().y));

		ball->set_velocity(Vect(ball->get_velocity().x * -1.0f, ball->get_velocity().y));

		demo_add_debug_hit(debug_data, Vect(0, ball->get_position().y), Vect(1, 0));
	}

	else if (ball->get_position().x > (demo_world_size.x - radius))
	{
		ball->set_position(Vect(ball->get_position().x -
			(ball->get_position().x - (demo_world_size.x - radius)) * 2.0f,
			ball->get_position().y));

		ball->set_velocity(Vect(ball->get_velocity().x * -1.0f, ball->get_velocity().y));

		demo_add_debug_hit(debug_data, Vect(demo_world_size.x, ball->get_position().y), Vect(-1, 0));
	}

	if (ball->get_position().y < radius)
	{
		ball->set_position(Vect(ball->get_position().x,
			ball->get_position().y + (radius - ball->get_position().y) * 2.0f));

		ball->set_velocity(Vect(ball->get_velocity().x, ball->get_velocity().y * -1.0f));

		demo_add_debug_hit(debug_data, Vect(ball->get_position().x, 0), Vect(0, 1));
	}
	else if (ball->get_position().y > (demo_world_size.y - radius))
	{
		ball->set_position(Vect(ball->get_position().x,
			ball->get_position().y - (ball->get_position().y - (demo_world_size.y - radius)) * 2.0f));

		ball->set_velocity(Vect(ball->get_velocity().x, ball->get_velocity().y * -1.0f));

		demo_add_debug_hit(debug_data, Vect(ball->get_position().x, demo_world_size.y), Vect(0, -1));
	}
}

void ArkanoidImpl::demo_draw(ImGuiIO& io, ImDrawList& draw_list)
{
	Vect demo_world_to_screen = level_controller.get()->get_world().get()->get_world_to_screen();
	Ball* ball = level_controller.get()->get_ball().get();

	Vect screen_pos = ball->get_position() * demo_world_to_screen;
	float screen_radius = ball->get_radius() * demo_world_to_screen.x;
	draw_list.AddCircleFilled(screen_pos, screen_radius, ImColor(100, 255, 100));


	for (std::shared_ptr<Brick> brick : *level_controller.get()->get_bricks().get())
	{
		Brick* temp = brick.get();
		draw_list.AddRectFilled(temp->get_position() * demo_world_to_screen,
			Vect((temp->get_position().x + temp->get_height()) * demo_world_to_screen.x,
				(temp->get_position().y + temp->get_width()) * demo_world_to_screen.y),
			ImColor(255, 0, 0, 255));
	}

	Carriage* carrige = level_controller.get()->get_carriage().get();
	draw_list.AddRectFilled(carrige->get_position() * demo_world_to_screen,
		Vect((carrige->get_position().x + carrige->get_width()) * demo_world_to_screen.x,
			(carrige->get_position().y + carrige->get_height()) * demo_world_to_screen.y),
		ImColor(0, 0, 255, 255));
}

void ArkanoidImpl::demo_add_debug_hit(ArkanoidDebugData& debug_data, const Vect& world_pos, const Vect& normal)
{
	Vect demo_world_to_screen = level_controller.get()->get_world().get()->get_world_to_screen();

	ArkanoidDebugData::Hit hit;
	hit.screen_pos = world_pos * demo_world_to_screen;
	hit.normal = normal;
	debug_data.hits.push_back(std::move(hit));
}


