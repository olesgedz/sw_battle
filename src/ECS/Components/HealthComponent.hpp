#pragma once

struct HealthComponent {
	int healthPoints;


	explicit HealthComponent(int  healthPoints = 0) :
	  healthPoints(healthPoints) {
	}
};