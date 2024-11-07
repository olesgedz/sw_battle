#pragma once

#include <cstdint>

struct MeleeAttackComponent {
	uint32_t healthPoints;


	explicit MeleeAttackComponent(uint32_t  healthPoints = 0) :
	  healthPoints(healthPoints) {
	}
};