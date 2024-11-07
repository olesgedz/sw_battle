#pragma once

#include "ECS/Ecs.hpp"
#include "ECS/Events.hpp"
#include "ECS/Components/MeleeAttackComponent.hpp"

class AttackSystem : public System {
public:
	AttackSystem() {
		requireComponent<MeleeAttackComponent>();
	}

	void subscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
	}
	
	void update() {
		std::cout << "Size" << getSystemEntities().size() << std::endl;
		
	}
};