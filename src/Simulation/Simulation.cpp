#include "Simulation.hpp"

#include "ECS/Components/HealthComponent.hpp"
#include "ECS/Components/AgilityComponent.hpp"
#include "ECS/Components/UnitComponent.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/StrengthComponent.hpp"
#include "ECS/Components/RangeAttackComponent.hpp"
#include "ECS/Components/MovementTargetComponent.hpp"
#include "ECS/Systems/AISystem.hpp"
#include "ECS/Systems/MovementSystem.hpp"
#include "IO/Commands/CreateMap.hpp"
#include "IO/Commands/SpawnSwordsman.hpp"

#include <fstream>

void Simulation::init() {
	_eventBus =  std::make_unique<EventBus>();
	_registry = std::make_unique<Registry>();

	_registry->addSystem<AISystem>();
	isRunning = true;

}


void  Simulation::_update() {
	_eventBus->reset();

	// Subscribe to events


	
	_registry->update();


	// System updates

	_registry->getSystem<AISystem>().update();
	// _registry->getSystem<AttackSystem>().update();
}



void  Simulation::stop() {

}

void  Simulation::run() {
	while (isRunning) {
		_update();
	}
}

void  Simulation::createMap(int width, int height)
{
	_map.width = width;
	_map.height = height;
	
	_map.data.resize(width * height);
	std::ranges::fill(_map.data, '_');
	printMap();
}

void  Simulation::printMap() const
{
	for (int y = 0; y < _map.height; ++y)
	{
		for (int x = 0; x < _map.width; ++x)
		{
			std::cout << _map.data[y * _map.width + x] << ' ';
		}
		std::cout << std::endl;
	}
}

void Simulation::addArcher(int gameId, int xPos, int yPos, int hp, int agility, int strength, int range)
{
	auto archer = std::make_shared<Entity>(_registry->createEntity());
	archer->addComponent<UnitComponent>(gameId, spawnOrder++);
	archer->addComponent<PositionComponent>(xPos, yPos);
	archer->addComponent<HealthComponent>(hp);
	archer->addComponent<AgilityComponent>(agility);
	archer->addComponent<StrengthComponent>(strength);
	archer->addComponent<RangeAttackComponent>(range);
	archer->addComponent<AIComponent>();
	units.insert({gameId, archer});
	
	std::cout << "Archer added" << std::endl;
}
void Simulation::addWarrior(int gameId, int xPos, int yPos, int hp, int strength)
{
	auto warrior = std::make_shared<Entity>(_registry->createEntity());
	warrior->addComponent<UnitComponent>(gameId, spawnOrder++);
	warrior->addComponent<PositionComponent>(xPos, yPos);
	warrior->addComponent<HealthComponent>(hp);
	warrior->addComponent<StrengthComponent>(strength);
	warrior->addComponent<AIComponent>();
	units.insert({gameId, warrior});
	
	std::cout << "Warrior added" << std::endl;
}

void Simulation::addMatchCommand(int gameId, int targetX, int targetY)
{
	if (units.contains(gameId))
	{
		units.at(gameId)->addComponent<MovementTargetComponent>(targetX, targetY);
	} else
	{
		throw std::runtime_error("Unit with gameId " + std::to_string(gameId) + " not found");
	}
}