#pragma once

#include "../base.h"

class Ball
{
public:
	Ball(Vect position, float radius, float speed);

	Vect get_position();
	void set_position(Vect position);

	Vect get_velocity();
	void set_velocity(Vect velocity);

	float get_radius();
	void set_radius(float radius);

	float get_speed();
	void set_speed(float speed);

	void reset(Vect position, float radius, float speed);
private:
	Vect position;
	Vect velocity = Vect(0.0f);

	float radius = 10.0f;
	float speed = 150.0f;
};

