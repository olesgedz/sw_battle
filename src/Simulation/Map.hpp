#pragma once

#include <vector>

class Map
{
	
public:
	Map(int width, int height);
	
	void setTile(int x, int y, char tile);
private:
	std::vector<char> data;
	int width;
	int height;
};