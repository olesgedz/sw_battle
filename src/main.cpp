#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/System/CommandParser.hpp>
#include <Simulation/Simulation.hpp>
#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
	using namespace sw;

	if (argc != 2)
	{
		throw std::runtime_error("Error: No file specified in command line argument");
	}

	std::ifstream file(argv[1]);
	if (!file)
	{
		throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
	}

	Simulation simulation;
	simulation.init();

	std::cout << "Commands:\n";

	io::CommandParser parser;

	parser.add<io::CreateMap>([&simulation](auto command) { simulation.createMap(command.width, command.height); });
	parser.add<io::SpawnSwordsman>(
		[&simulation](auto command)
		{ simulation.addWarrior(command.unitId, command.x, command.y, command.hp, command.strength); });
	parser.add<io::SpawnHunter>(
		[&simulation](auto command)
		{
			simulation.addArcher(
				command.unitId, command.x, command.y, command.hp, command.agility, command.strength, command.range);
		});
	parser.add<io::March>([&simulation](auto command)
						  { simulation.addMatchCommand(command.unitId, command.targetX, command.targetY); });

	std::cout << std::endl;

	parser.parse(file);

	simulation.run();
}
