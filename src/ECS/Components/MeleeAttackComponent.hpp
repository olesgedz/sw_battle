#pragma once

struct MeleeAttackComponent {
	int healthPoints;


	explicit MeleeAttackComponent(int  healthPoints = 0) :
	  healthPoints(healthPoints) {
	}
};