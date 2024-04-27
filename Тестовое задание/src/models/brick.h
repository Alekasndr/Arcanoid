#pragma once

#include "../base.h"

class Brick
{
public:
	Brick();
	Brick(Vect position, float height, float width);

	Vect get_position();
	void set_width(Vect position);

	float get_height();
	void set_height(float height);

	float get_width();
	void set_width(float width);

	float get_is_active();
	void set_is_active(float is_active);

	void reset(Vect position, float height, float width);
private:
	Vect position;
	float height;
	float width;
	bool is_active;
};

