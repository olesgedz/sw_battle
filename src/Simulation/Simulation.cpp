#include "Simulation.hpp"

#include "ECS/Components/HealthComponent.hpp"
#include "ECS/Components/AgilityComponent.hpp"
#include "ECS/Components/UnitComponent.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/StrengthComponent.hpp"
#include "ECS/Components/RangeAttackComponent.hpp"
#include "ECS/Components/MovementTargetComponent.hpp"
#include "ECS/Systems/AISystem.hpp"
#include "ECS/Systems/MoveSystem.hpp"
#include "IO/Commands/CreateMap.hpp"
#include "IO/Commands/SpawnSwordsman.hpp"

#include <fstream>

void Simulation::init() {
	_eventBus =  std::make_unique<EventBus>();
	_registry = std::make_unique<Registry>();


}

void Simulation::setup(sw::io::CommandParser& parser, std::ifstream& file) {
	// Add Systems
	_registry->addSystem<AISystem>();
	_registry->addSystem<AttackSystem>();

	// std::cout << "Commands:\n";
	// int mapWith = 0;
	// int mapHeight = 0;
	//
	// printMap();
	//
	// parser.parse(file);
	// createMap(10, 10);

}

void  Simulation::update() {
	_registry->update();

	_registry->getSystem<AttackSystem>().update();
}

void  Simulation::stop() {

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
	std::cout << " addArcher AAAA" << range << std::endl;
	Entity archer = _registry->createEntity();
	archer.addComponent<UnitComponent>(gameId, spawnOrder++);
	archer.addComponent<PositionComponent>(xPos, yPos);
	archer.addComponent<HealthComponent>(hp);
	archer.addComponent<AgilityComponent>(agility);
	archer.addComponent<StrengthComponent>(strength);
	// archer.addComponent<RangeAttackComponent>(range);
	units.insert({gameId, archer});
	
	std::cout << "Archer added" << std::endl;
}
void Simulation::addWarrior(int gameId, int xPos, int yPos, int hp, int strength)
{
	std::cout << " AAAA" << gameId << std::endl;
	Entity warrior = _registry->createEntity();
	warrior.addComponent<UnitComponent>(gameId, spawnOrder++);
	warrior.addComponent<PositionComponent>(xPos, yPos);
	warrior.addComponent<HealthComponent>(hp);
	warrior.addComponent<StrengthComponent>(strength);
	units.insert({gameId, warrior});
	
	std::cout << "Warrior added" << std::endl;
}
void Simulation::addMatchCommand(int gameId, int targetX, int targetY)
{
	// if (units.contains(gameId))
	// {
	// 	// units[gameId].addComponent<MovementTargetComponent>(targetX, targetX);
	// } else
	// {
	// 	throw std::runtime_error("Unit with gameId " + std::to_string(gameId) + " not found");
	// }
}