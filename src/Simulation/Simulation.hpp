#pragma once
#include "ECS/Ecs.hpp"
#include "ECS/Events.hpp"
#include "IO/System/EventLog.hpp"
#include "Simulation/Map.hpp"

#include <array>

class Simulation
{
public:
	Simulation() = default;
	void init();
	void run();
	void stop();
	void createMap(int width, int height);
	void _updateMap();

	void addWarrior(uint32_t gameId, uint32_t xPos, uint32_t yPos, uint32_t hp, uint32_t strength);
	void addArcher(
		uint32_t gameId,
		uint32_t xPos,
		uint32_t yPos,
		uint32_t hp,
		uint32_t agility,
		uint32_t strength,
		uint32_t range);
	void addMatchCommand(uint32_t gameId, uint32_t targetX, uint32_t targetY);

	static size_t getTurnNumber()
	{
		return turnNumber;
	}

private:
	void _update();

	bool isRunning = false;
	// GameID, Entity
	std::unordered_map<int, std::shared_ptr<Entity>> units;

	static size_t turnNumber;
	std::shared_ptr<EventBus> _eventBus;
	std::shared_ptr<Registry> _registry;

	std::shared_ptr<Map> _map;

	sw::EventLog eventLog;

	int spawnOrder = 0;
};
