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
		void setup(sw::io::CommandParser& parser, std::ifstream& file);
		void update();
		void stop();
	void createMap(int x, int y)
	{
		std::cout << "MAP SIZE" << x << " " << y  << std::endl;
	}
		
	private:
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
	
	void _initMap(int width, int height);

	void  printMap();

};
