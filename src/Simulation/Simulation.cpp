#include "Simulation.hpp"

#include "IO/Commands/CreateMap.hpp"
#include "IO/Commands/SpawnSwordsman.hpp"

#include <fstream>

void Simulation::init() {
	_eventBus =  std::make_unique<EventBus>();
	_registry = std::make_unique<Registry>();


}

void Simulation::setup(sw::io::CommandParser& parser, std::ifstream& file) {

	std::cout << "Commands:\n";
	// parser.add<sw::io::CreateMap>([](auto command) { printDebug(std::cout, command);})
	// .add<sw::io::SpawnSwordsman>([&](auto command)
	// {
		// printDebug(std::cout, command);
		Entity warrior = _registry->createEntity();

		warrior.addComponent<MeleeAttackComponent>();

	// });


	_initMap(10, 10);
	printMap();
	
	_registry->addSystem<AttackSystem>();
	
	std::cout << "Sanity check" << std::endl;




	_registry->update();

	_registry->getSystem<AttackSystem>().update();
	
	parser.parse(file);
}

void  Simulation::update() {
	
}

void  Simulation::stop() {

}

void  Simulation::_initMap(int width, int height)
{
	_map.width = width;
	_map.height = height;
	
	_map.data.resize(width * height);
	std::fill(_map.data.begin(), _map.data.end(), '_');
}

void  Simulation::printMap()
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