#pragma once

#include "../base.h"

class Ball
{
public:
	Ball(Vect position, float radius, float speed);

	Vect get_position();
	void set_width(Vect position);

	float get_radius();
	void set_radius(float radius);

	float get_speed();
	void set_speed(float speed);

	void reset(Vect position, float radius, float speed);
private:
	Vect position;
	float radius = 10.0f;
	float speed = 150.0f;
};

