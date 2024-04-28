#include "level_generator.h"

std::shared_ptr<std::vector<std::shared_ptr<Brick>>> LevelGenerator::create_bricks_list(const ArkanoidSettings& settings)
{
	std::shared_ptr<std::vector<std::shared_ptr<Brick>>> bricks = std::make_shared<std::vector<std::shared_ptr<Brick>>>();
	bricks->reserve(settings.bricks_columns_count * settings.bricks_rows_count);

	float width = (settings.world_size.x - (settings.bricks_columns_padding * settings.bricks_columns_count + 1.0f))
		/ settings.bricks_columns_count;
	float height = ((settings.world_size.y / 5.0f) - (settings.bricks_rows_padding * settings.bricks_rows_count + 1.0f))
		/ settings.bricks_rows_count;

	for (int i = 0; i < settings.bricks_columns_count; i++) {
		for (int j = 0; j < settings.bricks_rows_count; j++) {
			std::shared_ptr<Brick> brick = std::make_shared<Brick>(Vect(settings.bricks_columns_padding * (i + 1) + width * i,
				settings.bricks_rows_padding * (j + 1) + height * j), width, height);
			bricks.get()->push_back(brick);
		}
	}

	return bricks;
}

void LevelGenerator::reset_bricks_list(std::shared_ptr<std::vector<std::shared_ptr<Brick>>> briks, const ArkanoidSettings& settings)
{
	float width = (settings.world_size.x - (settings.bricks_columns_padding * settings.bricks_columns_count + 1.0f))
		/ settings.bricks_columns_count;
	float height = ((settings.world_size.y / 5.0f) - (settings.bricks_rows_padding * settings.bricks_rows_count + 1.0f))
		/ settings.bricks_rows_count;

	int count = 0;
	for (int i = 0; i < settings.bricks_columns_count; i++) {
		for (int j = 0; j < settings.bricks_rows_count; j++) {

			briks.get()->at(count).get()->reset(Vect(settings.bricks_columns_padding * (i + 1) + width * i,
				settings.bricks_rows_padding * (j + 1) + height * j), width, height);
			count++;
		}
	}
}