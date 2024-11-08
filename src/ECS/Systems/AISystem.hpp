#pragma once

#include "ECS/Components/AIComponent.hpp"
#include "ECS/Components/HealthComponent.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/UnitComponent.hpp"
#include "ECS/Ecs.hpp"
#include "ECS/Events.hpp"
#include "IO/System/EventLog.hpp"
#include "Simulation/Map.hpp"

class AISystem : public System
{
public:
	AISystem()
	{
		requireComponent<AIComponent>();
		requireComponent<PositionComponent>();
		requireComponent<HealthComponent>();
		requireComponent<UnitComponent>();
	}

	void update(std::shared_ptr<Map> map, bool& isRunning);
	void meleeBehavior(Entity& entity, std::shared_ptr<Map> map);
	void rangeBehavior(Entity& entity, std::shared_ptr<Map> map);
	void moveBehavior(Entity& entity, std::shared_ptr<Map> map);
	bool areInRange(Entity& entity, Entity& other, int range);
	bool checkIfFinish();

private:
	sw::EventLog eventLog;
};
