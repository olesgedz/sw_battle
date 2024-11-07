#pragma once

#include "ECS/Ecs.hpp"
#include "ECS/Events.hpp"
#include "ECS/Components/AIComponent.hpp"

class AISystem : public System {
public:
  AISystem() {
    requireComponent<AIComponent>();
  }

  void subscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
  }
	
  void update() {
    std::cout << "Size" << getSystemEntities().size() << std::endl;
		
  }
};