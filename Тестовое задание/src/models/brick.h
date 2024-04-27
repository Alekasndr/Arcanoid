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

	void reset(Vect position, float height, float width);
private:
	Vect position;
	float height;
	float width;
};

