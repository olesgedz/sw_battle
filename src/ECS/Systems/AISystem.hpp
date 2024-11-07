#pragma once

#include <algorithm>

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
    auto entities = getSystemEntities();

    std::ranges::sort(entities, [](Entity& a, Entity& b) {
  return a.getComponent<UnitComponent>().spawnOrder < b.getComponent<UnitComponent>().spawnOrder;
});

    for (auto& entity : entities) {
	  auto& aiComponent = entity.getComponent<AIComponent>();
      auto entityOrder = entity.getComponent<UnitComponent>().spawnOrder;
      std::cout << "AI System: id " << entity.getId()  << "   spawn order entityOrder: " << entityOrder << std::endl;
	  // Do AI stuff
	}
		
  }
};