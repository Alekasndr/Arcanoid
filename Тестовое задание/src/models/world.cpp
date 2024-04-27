#include "world.h"

World::World(Vect size)
{
	this->size = size;
}

Vect World::get_world_size()
{
	return size;
}

void World::set_world_size(Vect world_size)
{
	this->size = world_size;
}

Vect World::get_world_to_screen()
{
	return world_to_screen;
}

void World::set_world_to_screen(Vect world_to_screen)
{
	this->world_to_screen = world_to_screen;
}

void World::reset(Vect size)
{
	this->size = size;
}
