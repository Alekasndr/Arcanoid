#pragma once

#include "arkanoid.h"
#include "models/brick.h"
#include "models/world.h"
#include "models/carriage.h"
#include "controllers/level_controller.h"

#define USE_ARKANOID_IMPL

class ArkanoidImpl : public Arkanoid
{
public:
	void reset(const ArkanoidSettings& settings) override;
	void update(ImGuiIO& io, ArkanoidDebugData& debug_data, float elapsed) override;
	void draw(ImGuiIO& io, ImDrawList& draw_list) override;

private:
	void demo_draw(ImGuiIO& io, ImDrawList& draw_list);

	std::unique_ptr<LevelController> level_controller;
};
