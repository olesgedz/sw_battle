#pragma once
#include <array>
#include "ECS/Ecs.hpp"
#include "ECS/Events.hpp"
#include "ECS/Systems/AttackSystem.hpp"
#include "ECS/Components/MeleeAttackComponent.hpp"



class Simulation {
	
	public:
		Simulation() = default;
		void init();
		void setup();
		void update();
		void stop();
		
	private:
	size_t turnNumber = 0;

};
