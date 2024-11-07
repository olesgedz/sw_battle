#pragma once

#include "ECS/Ecs.hpp"
#include "ECS/Events.hpp"


class AttackEvent : public Event {
public:
	int damageHitPoints;
	Entity attacker;
	Entity target;
	
	AttackEvent(Entity attacker, Entity target, int damageHitPoints)
			: attacker(attacker), target(target), damageHitPoints(damageHitPoints) {
	}
};