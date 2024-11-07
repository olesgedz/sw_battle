#pragma once

struct MovementTargetComponent {

	int x;
	int y;


	explicit MovementTargetComponent(int x = 0, int y = 0) :
	  x(x), y(y) {
	}
};