#include "Map.hpp"
#include <algorithm>

Map::Map(int width, int height) : width(width), height(height)
{
	data.resize(width * height);
	std::ranges::fill(data, '_');
}

void Map::setTile(int x, int y, char tile)
{
	data[y * width + x] = tile;
}