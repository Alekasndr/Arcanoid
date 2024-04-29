#include "ball.h"

Ball::Ball(Vect position, float radius, float speed)
{
	this->position = position;
	this->radius = radius;
	this->speed = speed;
	this->velocity = Vect(speed);
	this->is_active = true;
}

Vect Ball::get_position()
{
	return position;
}

void Ball::set_position(Vect position)
{
	this->position = position;
}

Vect Ball::get_velocity()
{
	return velocity;
}

void Ball::set_velocity(Vect velocity)
{
	this->velocity = velocity;
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

float Ball::get_is_active()
{
	return is_active;
}

void Ball::set_is_active(float is_active)
{
	this->is_active = is_active;
}

void Ball::reset(Vect position, float radius, float speed)
{
	this->position = position;
	this->radius = radius;
	this->speed = speed;
	this->velocity = Vect(speed);
	this->is_active = true;
}

