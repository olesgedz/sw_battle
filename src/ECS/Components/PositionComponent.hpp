#pragma once

struct PositionComponent
{
	int x;
	int y;

	explicit PositionComponent(int x = 0, int y = 0) :
			x(x),
			y(y)
	{}
};
