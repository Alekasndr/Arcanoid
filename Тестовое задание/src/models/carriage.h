#pragma once

#include "../base.h"

class Carriage
{
public:
	Carriage(Vect position, float width);

	Vect get_position();
	void set_position(Vect position);

	float get_height();

	float get_width();
	void set_width(float width);

	float get_speed();
	void set_speed(float speed);

	void reset(Vect position, float width);
private:
	Vect position;
	float height = 10.0f;
	float width = 100.0f;
	float speed = 10.0f;
};

