#include "level_generator.h"

std::shared_ptr<std::vector<std::shared_ptr<Brick>>> LevelGenerator::create_blocks_list(const ArkanoidSettings& settings)
{
	std::shared_ptr<std::vector<std::shared_ptr<Brick>>> blocks = std::make_unique<std::vector<std::shared_ptr<Brick>>>();
	blocks->reserve(settings.bricks_columns_count * settings.bricks_rows_count);

	float width = (settings.world_size.x - settings.bricks_columns_padding * (settings.bricks_columns_count + 1.0f)) / settings.bricks_columns_count;
	float height = ((settings.world_size.x / 5.0f) - settings.bricks_rows_count * (settings.bricks_rows_count + 1.0f)) / settings.bricks_rows_count;

	for (int i = 0; i < settings.bricks_columns_count; i++) {
		for (int j = 0; j < settings.bricks_rows_count; j++) {
			std::shared_ptr<Brick> brick = std::make_shared <Brick>(Vect(settings.bricks_columns_padding * (i + 1.0f) + width * i,
				settings.bricks_rows_padding * (j + 1.0f) + height * j), width, height);
			blocks->push_back(brick);
		}
	}

	return blocks;
}
