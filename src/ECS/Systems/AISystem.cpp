#include "AISystem.hpp"

#include "ECS/Components/AIComponent.hpp"
#include "ECS/Components/AgilityComponent.hpp"
#include "ECS/Components/MeleeAttackComponent.hpp"
#include "ECS/Components/MovementTargetComponent.hpp"
#include "ECS/Components/RangeAttackComponent.hpp"
#include "ECS/Components/StrengthComponent.hpp"
#include "ECS/Components/UnitComponent.hpp"
#include "ECS/Ecs.hpp"
#include "ECS/Events.hpp"
#include "Helpers/Math.hpp"
#include "IO/Events/UnitAttacked.hpp"
#include "IO/Events/UnitDied.hpp"
#include "IO/Events/UnitMoved.hpp"
#include "Simulation/Simulation.hpp"

void AISystem::update(std::shared_ptr<Map> map)
{
	auto entities = getSystemEntities();

	std::ranges::sort(
		entities,
		[](Entity& a, Entity& b)
		{ return a.getComponent<UnitComponent>().spawnOrder < b.getComponent<UnitComponent>().spawnOrder; });

	for (auto& entity : entities)
	{
		if (!entity.getComponent<AIComponent>().alive)
		{
			continue;
		}
		
		if (entity.hasComponent<RangeAttackComponent>())
		{
			rangeBehavior(entity, map);
		}
		else if (entity.hasComponent<MeleeAttackComponent>())
		{
			meleeBehavior(entity, map);
		}
	}
}


void AISystem::meleeBehavior(Entity& entity, std::shared_ptr<Map> map)
{
	bool canAttack = false;
	for (auto& otherEntity: getSystemEntities())
	{
		if (otherEntity == entity)
		{
			continue;
		}

		if (areInRange( entity,  otherEntity, 1))
		{
			canAttack = true;
			
			auto& health = otherEntity.getComponent<HealthComponent>();
			health.healthPoints -= entity.getComponent<StrengthComponent>().strength;

	
			uint32_t attackerUnitId = entity.getComponent<UnitComponent>().gameId;
			uint32_t targetUnitId = otherEntity.getComponent<UnitComponent>().gameId;
			uint32_t damage = entity.getComponent<StrengthComponent>().strength;
			uint32_t targetHp = health.healthPoints;
			eventLog.log(Simulation::getTurnNumber(), sw::io::UnitAttacked{attackerUnitId, targetUnitId, damage, targetHp});
			if (targetHp <= 0)
			{
				otherEntity.getComponent<AIComponent>().alive = false;
				eventLog.log(Simulation::getTurnNumber(), sw::io::UnitDied{targetUnitId});
				otherEntity.kill();
			}
		}
	}

	if (!canAttack)
	{
		if (entity.hasComponent<MovementTargetComponent>())
		{
			auto& position = entity.getComponent<PositionComponent>();
			const auto target = entity.getComponent<MovementTargetComponent>();
			unsigned int id = entity.getComponent<UnitComponent>().gameId;
			int targetDirectionX = target.x - position.x;
			int targetDirectionY = target.y - position.y;

			normalize(targetDirectionX, targetDirectionY);
			if (targetDirectionX != 0 || targetDirectionY != 0)
			{
				position.x += targetDirectionX;
				position.y += targetDirectionY;

				unsigned int posX = position.x;
				unsigned int posY = position.y;
				eventLog.log(Simulation::getTurnNumber(), sw::io::UnitMoved{id, posX, posY});
			}
		}
	}
}

void AISystem::rangeBehavior(Entity& entity, std::shared_ptr<Map> map)
{
	bool canAttack = false;
	for (auto& otherEntity: getSystemEntities())
	{
		if (otherEntity == entity)
		{
			continue;
		}

		if (areInRange( entity,  otherEntity, 1))
		{
			canAttack = true;
			
			auto& health = otherEntity.getComponent<HealthComponent>();
			health.healthPoints -= entity.getComponent<StrengthComponent>().strength;

	
			uint32_t attackerUnitId = entity.getComponent<UnitComponent>().gameId;
			uint32_t targetUnitId = otherEntity.getComponent<UnitComponent>().gameId;
			uint32_t damage = entity.getComponent<StrengthComponent>().strength;
			uint32_t targetHp = health.healthPoints;

			eventLog.log(Simulation::getTurnNumber(), sw::io::UnitAttacked{attackerUnitId, targetUnitId, damage, targetHp});

			if (targetHp <= 0)
			{
				otherEntity.getComponent<AIComponent>().alive = false;
				eventLog.log(Simulation::getTurnNumber(), sw::io::UnitDied{targetUnitId});
				otherEntity.kill();
			}
		}
	}

	if (!canAttack)
	{
		for (auto& otherEntity: getSystemEntities())
		{
			if (otherEntity == entity)
			{
				continue;
			}

			if (areInRange( entity,  otherEntity, entity.getComponent<RangeAttackComponent>().range))
			{
				canAttack = true;
			
				auto& health = otherEntity.getComponent<HealthComponent>();
				health.healthPoints -= entity.getComponent<AgilityComponent>().agility;

	
				uint32_t attackerUnitId = entity.getComponent<UnitComponent>().gameId;
				uint32_t targetUnitId = otherEntity.getComponent<UnitComponent>().gameId;
				uint32_t damage = entity.getComponent<AgilityComponent>().agility;
				uint32_t targetHp = health.healthPoints;
			
				eventLog.log(Simulation::getTurnNumber(), sw::io::UnitAttacked{attackerUnitId, targetUnitId, damage, targetHp});

				if (targetHp <= 0)
				{
					otherEntity.getComponent<AIComponent>().alive = false;
					eventLog.log(Simulation::getTurnNumber(), sw::io::UnitDied{targetUnitId});
					otherEntity.kill();
				}
			}
		}
	}

	if (!canAttack)
	{
		if (entity.hasComponent<MovementTargetComponent>())
		{
			auto& position = entity.getComponent<PositionComponent>();
			const auto target = entity.getComponent<MovementTargetComponent>();
			unsigned int id = entity.getComponent<UnitComponent>().gameId;
			int targetDirectionX = target.x - position.x;
			int targetDirectionY = target.y - position.y;

			normalize(targetDirectionX, targetDirectionY);
			if (targetDirectionX != 0 || targetDirectionY != 0)
			{
				position.x += targetDirectionX;
				position.y += targetDirectionY;

				unsigned int posX = position.x;
				unsigned int posY = position.y;
				eventLog.log(Simulation::getTurnNumber(), sw::io::UnitMoved{id, posX, posY});
			}
		}
	}
}

bool AISystem::areInRange( Entity& entity,  Entity& other, int range) {

	auto [x, y] = entity.getComponent<PositionComponent>();
	auto [otherX, otherY] = other.getComponent<PositionComponent>();
	
	int dx = x - otherX;
	int dy = y - otherY;
	int distanceSquared = dx * dx + dy * dy;
	return distanceSquared <= range * range; 
}
