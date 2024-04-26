#include "carriage.h"

Carriage::Carriage(Vect position, float width)
{
	this->position = position;
	this->width = width;
}

Vect Carriage::get_position()
{
	return position;
}

void Carriage::set_position(Vect position)
{
	this->position = position;
}

float Carriage::get_height()
{
	return height;
}

float Carriage::get_width()
{
	return width;
}

void Carriage::set_width(float width)
{
	width = width;
}

float Carriage::get_speed()
{
	return speed;
}

void Carriage::set_speed(float speed)
{
	this->speed = speed;
}



