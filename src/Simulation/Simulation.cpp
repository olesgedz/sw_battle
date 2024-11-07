#include "Simulation.hpp"

#include "ECS/Components/AgilityComponent.hpp"
#include "ECS/Components/HealthComponent.hpp"
#include "ECS/Components/MovementTargetComponent.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/RangeAttackComponent.hpp"
#include "ECS/Components/StrengthComponent.hpp"
#include "ECS/Components/UnitComponent.hpp"
#include "ECS/Systems/AISystem.hpp"
#include "ECS/Systems/MovementSystem.hpp"
#include "IO/Commands/CreateMap.hpp"
#include "IO/Commands/SpawnSwordsman.hpp"
#include "IO/Events/MapCreated.hpp"
#include "IO/Events/MarchStarted.hpp"
#include "IO/Events/UnitSpawned.hpp"

#include <fstream>

size_t Simulation::turnNumber = 1;

void Simulation::init()
{
	_eventBus = std::make_unique<EventBus>();
	_registry = std::make_unique<Registry>();

	_registry->addSystem<AISystem>();
	isRunning = true;
	turnNumber = 1;
}

void Simulation::_update()
{
	_eventBus->reset();

	// Subscribe to events

	_registry->update();

	// System updates

	_registry->getSystem<AISystem>().update(_map);
	// _registry->getSystem<AttackSystem>().update();
}

void Simulation::stop() {}

void Simulation::_updateMap()
{
	for (auto& [gameId, entity] : units)
	{
		auto [x, y] = entity->getComponent<PositionComponent>();
		auto info = entity->getComponent<UnitComponent>();
		_map->setTile(x, y, info.gameId);
	}
}

void Simulation::run()
{
	_updateMap();
	while (isRunning)
	{	turnNumber++;
		_update();
	}
}

void Simulation::createMap(int width, int height)
{
	_map = std::make_shared<Map>(width, height);
	eventLog.log(turnNumber, sw::io::MapCreated{static_cast<uint32_t>(width), static_cast<uint32_t>(height)});
}

void Simulation::addArcher(
	uint32_t gameId, uint32_t xPos, uint32_t yPos, uint32_t hp, uint32_t agility, uint32_t strength, uint32_t range)
{
	auto archer = std::make_shared<Entity>(_registry->createEntity());
	archer->addComponent<UnitComponent>(gameId, spawnOrder++);
	archer->addComponent<PositionComponent>(xPos, yPos);
	archer->addComponent<HealthComponent>(hp);
	archer->addComponent<MeleeAttackComponent>(hp);
	archer->addComponent<AgilityComponent>(agility);
	archer->addComponent<StrengthComponent>(strength);
	archer->addComponent<RangeAttackComponent>(range);
	archer->addComponent<AIComponent>();
	units.insert({gameId, archer});

	eventLog.log(
		turnNumber,
		sw::io::UnitSpawned{
			gameId,
			"Hunter",
			xPos,
			yPos,
		});
}

void Simulation::addWarrior(uint32_t gameId, uint32_t xPos, uint32_t yPos, uint32_t hp, uint32_t strength)
{
	auto warrior = std::make_shared<Entity>(_registry->createEntity());
	warrior->addComponent<UnitComponent>(gameId, spawnOrder++);
	warrior->addComponent<PositionComponent>(xPos, yPos);
	warrior->addComponent<HealthComponent>(hp);
	warrior->addComponent<MeleeAttackComponent>(hp);
	warrior->addComponent<StrengthComponent>(strength);
	warrior->addComponent<AIComponent>();
	units.insert({gameId, warrior});

	eventLog.log(
		turnNumber,
		sw::io::UnitSpawned{
			gameId,
			"Swordsman",
			xPos,
			yPos,
		});
}

void Simulation::addMatchCommand(uint32_t gameId, uint32_t targetX, uint32_t targetY)
{
	if (units.contains(gameId))
	{
		units.at(gameId)->addComponent<MovementTargetComponent>(targetX, targetY);
		auto currentPosition = units.at(gameId)->getComponent<PositionComponent>();
		uint32_t currentPostitionX = currentPosition.x;
		uint32_t currentPostitionY = currentPosition.y;

		eventLog.log(turnNumber, sw::io::MarchStarted{gameId, currentPostitionX, currentPostitionY, targetX, targetY});
	}
	else
	{
		throw std::runtime_error("Unit with gameId " + std::to_string(gameId) + " not found");
	}
}
