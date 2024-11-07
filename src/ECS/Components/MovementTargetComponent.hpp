#pragma once

struct MovementTargetComponent {
	int range;


	explicit MovementTargetComponent(int  range = 0, int x = 0) :
	  range(range) {
	}
};