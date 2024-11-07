#include "Simulation.hpp"


void Simulation::init() {
	std::shared_ptr<EventBus> eventBus =  std::make_unique<EventBus>();
	std::shared_ptr<Registry> registry = std::make_unique<Registry>();

	registry->addSystem<AttackSystem>();
	
	std::cout << "Sanity check" << std::endl;



	Entity warrior = registry->createEntity();

	warrior.addComponent<MeleeAttackComponent>();

	registry->update();

	registry->getSystem<AttackSystem>().update();
}

void  Simulation::setup() {
}

void  Simulation::update() {
	
}

void  Simulation::stop() {

}
		