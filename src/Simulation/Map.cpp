#include "Map.hpp"

#include <algorithm>

Map::Map(int width, int height) :
		width(width),
		height(height)
{
	data.resize(width * height);
	std::ranges::fill(data, '_');
}

void Map::setTile(int x, int y, char tile)
{
	data[y * width + x] = tile;
}

bool Map::checkBounds(int x, int y) const
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		return true;
	}
	return false;
}
