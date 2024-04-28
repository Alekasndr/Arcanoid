#include "brick.h"

Brick::Brick()
{
}

Brick::Brick(Vect position, float width, float height)
{
	this->width = width;
	this->height = height;
	this->position = position;
	this->is_active = true;
}

Vect Brick::get_position()
{
	return position;
}

void Brick::set_width(Vect position)
{
	this->position = position;
}

float Brick::get_height()
{
	return height;
}

void Brick::set_height(float height)
{
	this->height = height;
}

float Brick::get_width()
{
	return width;
}

void Brick::set_width(float width)
{
	this->width = width;
}

float Brick::get_is_active()
{
	return is_active;
}

void Brick::set_is_active(float is_active)
{
	this->is_active = is_active;
}

void Brick::reset(Vect position, float width, float height)
{
	this->width = width;
	this->height = height;
	this->position = position;
	this->is_active = true;
}
