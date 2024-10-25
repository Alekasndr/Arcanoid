#include "level_generator.h"

std::vector<Brick> LevelGenerator::create_bricks_list(const ArkanoidSettings& settings)
{
	std::vector<Brick> bricks;
	bricks.reserve(settings.bricks_columns_count * settings.bricks_rows_count);

	float width = (settings.world_size.x - (settings.bricks_columns_padding * settings.bricks_columns_count + 1.0f))
		/ settings.bricks_columns_count;
	float height = ((settings.world_size.y / 3.0f) - (settings.bricks_rows_padding * settings.bricks_rows_count + 1.0f))
		/ settings.bricks_rows_count;

	for (int i = 0; i < settings.bricks_columns_count; i++) {
		for (int j = 0; j < settings.bricks_rows_count; j++) {
			bricks.emplace_back(Vect(settings.bricks_columns_padding * (i + 1) + width * i,
				settings.bricks_rows_padding * (j + 1) + height * j), width, height);
		}
	}
	return bricks;
}

void LevelGenerator::reset_bricks_list(std::vector<Brick>& briks, const ArkanoidSettings& settings)
{
	float width = (settings.world_size.x - (settings.bricks_columns_padding * settings.bricks_columns_count + 1.0f))
		/ settings.bricks_columns_count;
	float height = ((settings.world_size.y / 3.0f) - (settings.bricks_rows_padding * settings.bricks_rows_count + 1.0f))
		/ settings.bricks_rows_count;

	int count = 0;
	for (int i = 0; i < settings.bricks_columns_count; i++) {
		for (int j = 0; j < settings.bricks_rows_count; j++) {
			briks[count].reset(Vect(settings.bricks_columns_padding * (i + 1) + width * i,
				settings.bricks_rows_padding * (j + 1) + height * j), width, height);
			count++;
		}
	}
}