#pragma once

#include "../base.h"

class World
{
public:
	World(Vect size);

	Vect get_world_size();
	void set_world_size(Vect size);

	Vect get_world_to_screen();
	void set_world_to_screen(Vect world_to_screen);

	void reset(Vect size);
private:
	Vect size = Vect(0.0f);
	Vect world_to_screen = Vect(0.0f);;
};

