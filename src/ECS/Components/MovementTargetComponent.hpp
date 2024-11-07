#pragma once

struct MovementTargetComponent {
	int x;
	int y;

	explicit MovementTargetComponent(int x, int y) : x (x), y (y) {
	}
};