#include "brick.h"

Brick::Brick(Vect position, float height, float width)
{
	this->height = height;
	this->width = width;
	this->position = position;
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
