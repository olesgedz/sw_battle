#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/Events/MapCreated.hpp>
#include <IO/Events/MarchEnded.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/UnitAttacked.hpp>
#include <IO/Events/UnitDied.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/System/CommandParser.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/System/PrintDebug.hpp>
#include <fstream>
#include <iostream>



class BaseWarrior
{
public:
	virtual ~BaseWarrior() = default;
	virtual void Think() = 0;
};


class IMove
{
	virtual void Move() = 0; 
};

class IAttack
{
	virtual void Attack() = 0;
};

class SwordWarrior : public  BaseWarrior, IAttack, IMove
{
public:
    int x = 0;
	int y = 0;

	SwordWarrior(int x, int y) : x(x), y(y) {};

	
	void Think() override
	{
		std::cout << "Swordman Think" << std::endl;
		std::cout << "Position " << x << " " << y << std::endl;
		if (x > 3)
		{
			Attack();
		} else
		{
			Move();
		}
		

	}

	void Move() override
	{
		std::cout << "Swordman moved" << std::endl;
		x-=1;
		y -= 2;
		std::cout << "Swordman moved to " << x << " " << y << std::endl;

	}
	
	void Attack() override
	{
		std::cout << " Swordman Attack" << std::endl;
	}
	
};

class ArcherWarrior : public BaseWarrior, IAttack, IMove
{
public:

	int x = 0;
	int y = 0;

	ArcherWarrior(int x, int y) : x(x), y(y) {};
	
	void Think() override
	{
		std::cout << "ArcherWarrior Think" << std::endl;
		std::cout << "Position " << x << " " << y << std::endl;

		if (x > 5)
		{
			Attack();
		} else
		{
			Move();
		}
		
	}
	
	void Move() override
	{
		std::cout << "ArcherWarrior moved" << std::endl;
		x += 2;
		std::cout << "ArcherWarrior moved to " << x << " " << y << std::endl;

	}
	

	void Attack() override
	{
		std::cout << "Attack in Range" << std::endl;
	}
};

int main(int argc, char** argv)
{
	std::vector<std::shared_ptr<BaseWarrior>> gameObjects;
	
	gameObjects.emplace_back(std::make_shared<ArcherWarrior>(-10, 0));
	gameObjects.emplace_back(std::make_shared<SwordWarrior>(5, -10));

for (int i = 0; i < 20; i++)
{
	for (auto& character : gameObjects)
	{
		character->Think();
	}
}

	
}



// int main(int argc, char** argv)
// {
// 	// using namespace sw;
// 	//
// 	// if (argc != 2)
// 	// {
// 	// 	throw std::runtime_error("Error: No file specified in command line argument");
// 	// }
// 	//
// 	// std::ifstream file(argv[1]);
// 	// if (!file)
// 	// {
// 	// 	throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
// 	// }
// 	//
// 	// // Code for example...
// 	//
// 	// std::cout << "Commands:\n";
// 	// io::CommandParser parser;
// 	// parser.add<io::CreateMap>([](auto command) { printDebug(std::cout, command); })
// 	// 	.add<io::SpawnSwordsman>([](auto command) { printDebug(std::cout, command); })
// 	// 	.add<io::SpawnHunter>([](auto command) { printDebug(std::cout, command); })
// 	// 	.add<io::March>([](auto command) { printDebug(std::cout, command); });
// 	//
// 	// parser.parse(file);
// 	//
// 	// std::cout << "\n\nEvents:\n";
// 	//
// 	// EventLog eventLog;
// 	//
// 	// eventLog.log(1, io::MapCreated{10, 10});
// 	// eventLog.log(1, io::UnitSpawned{1, "Swordsman", 0, 0});
// 	// eventLog.log(1, io::UnitSpawned{2, "Hunter", 9, 0});
// 	// eventLog.log(1, io::MarchStarted{1, 0, 0, 9, 0});
// 	// eventLog.log(1, io::MarchStarted{2, 9, 0, 0, 0});
// 	// eventLog.log(1, io::UnitSpawned{3, "Swordsman", 0, 9});
// 	// eventLog.log(1, io::MarchStarted{3, 0, 9, 0, 0});
// 	//
// 	// eventLog.log(2, io::UnitMoved{1, 1, 0});
// 	// eventLog.log(2, io::UnitMoved{2, 8, 0});
// 	// eventLog.log(2, io::UnitMoved{3, 0, 8});
// 	//
// 	// eventLog.log(3, io::UnitMoved{1, 2, 0});
// 	// eventLog.log(3, io::UnitMoved{2, 7, 0});
// 	// eventLog.log(3, io::UnitMoved{3, 0, 7});
// 	//
// 	// eventLog.log(4, io::UnitMoved{1, 3, 0});
// 	// eventLog.log(4, io::UnitAttacked{2, 1, 5, 0});
// 	// eventLog.log(4, io::UnitDied{1});
// 	// eventLog.log(4, io::UnitMoved{3, 0, 6});
// 	//
// 	// eventLog.log(5, io::UnitMoved{2, 6, 0});
// 	// eventLog.log(5, io::UnitMoved{3, 0, 5});
// 	//
// 	// eventLog.log(6, io::UnitMoved{2, 5, 0});
// 	// eventLog.log(6, io::UnitMoved{3, 0, 4});
// 	//
// 	// eventLog.log(7, io::UnitAttacked{2, 3, 5, 5});
// 	// eventLog.log(7, io::UnitMoved{3, 0, 3});
// 	//
// 	// eventLog.log(8, io::UnitAttacked{2, 3, 5, 0});
// 	// eventLog.log(8, io::UnitDied{3});
// 	//
// 	//
// 	//
//
//
// 	
//
// 	return 0;
// }
