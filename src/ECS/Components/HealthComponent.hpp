#pragma once

#include <cstdint>

struct HealthComponent {
	uint32_t healthPoints;


	explicit HealthComponent(uint32_t  healthPoints = 0) :
	  healthPoints(healthPoints) {
	}
};