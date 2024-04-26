#include "ball.h"

Ball::Ball(Vect position, float radius, float speed)
{
	this->position = position;
	this->radius = radius;
	this->speed = speed;
}

Vect Ball::get_position()
{
	return position;
}

void Ball::set_width(Vect position)
{
	this->position = position;
}

float Ball::get_radius()
{
	return radius;
}

void Ball::set_radius(float radius)
{
	this->radius = radius;
}

float Ball::get_speed()
{
	return speed;
}

void Ball::set_speed(float speed)
{
	this->speed = speed;
}

