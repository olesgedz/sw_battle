#pragma once
#include "ECS/Components/MeleeAttackComponent.hpp"
#include "ECS/Ecs.hpp"
#include "ECS/Events.hpp"
#include "ECS/Systems/AttackSystem.hpp"
#include "IO/System/CommandParser.hpp"

#include <array>

class Simulation {
	
	public:
		Simulation() = default;
		void init();
		void run();
		void stop();
	void createMap(int width, int height);

	void addWarrior(int gameId, int xPos, int yPos, int hp, int strength);
	void addArcher(int gameId, int xPos, int yPos, int hp, int agility, int strength, int range);
	void addMatchCommand(int gameId, int targetX, int targetY);
	

	private:
	void _update();

	bool isRunning = false; 
	// GameID, Entity
	std::unordered_map<int, std::shared_ptr<Entity>> units;
	
	size_t turnNumber = 0;
	std::shared_ptr<EventBus> _eventBus;
	std::shared_ptr<Registry> _registry;

	struct Map
	{
		std::vector<char> data;
		int width;
		int height;
	};
	Map _map;
	
	int spawnOrder = 0;

	void  printMap() const;


};
