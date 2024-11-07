#pragma once


struct PositionComponent {
	float x;
	float y;

	explicit PositionComponent(float x = 0, float y = 0) :
	  x(x), y(y) {
	}
};