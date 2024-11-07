#include "Ecs.hpp"


size_t BaseComponent::_nextId = 0;

void Entity::kill() const {
	registry->killEntity(*this);
}


Entity Registry::createEntity() {
	size_t entityId;
	if (_freedIds.empty()) {
		entityId = _numEntities++;

		if (entityId >= _entityComponentSignatures.size()) {
			_entityComponentSignatures.resize(entityId + 1);
		}
	} else {
		entityId = _freedIds.front();
		_freedIds.pop_front();
	}

	Entity entity(entityId);
	entity.registry = this;
	_entitiesToBeAdded.insert(entity);
	if (entityId >= _entityComponentSignatures.size()) {
		_entityComponentSignatures.resize(entityId + 1);
	}


	return entity;
}

void Registry::killEntity(Entity entity) {
	_entitiesToBeKilled.insert(entity);
}


void Registry::update() {
	// Actually add/remove  the entities between frames
	for (const auto& entity : _entitiesToBeAdded) {
		addEntityToSystem(entity);
	}
	_entitiesToBeAdded.clear();

	for (auto entity : _entitiesToBeKilled) {
		removeEntityFromSystems(entity);

		_entityComponentSignatures[entity.getId()].reset();
		// add to freed ids
		_freedIds.push_back(entity.getId());
	}
	_entitiesToBeKilled.clear();
}

void Registry::addEntityToSystem(Entity entity) {
	const auto entityId = entity.getId();

	const auto& entitySignature = _entityComponentSignatures[entityId];

	// loop all the systems
	for (auto& system : _systems) {
		const auto& systemSignature = system.second->getComponentSignature();

		// Check if the entity signature matches the system signature
		if ((entitySignature & systemSignature) == systemSignature) {
			system.second->addEntity(entity);
		}
	}
}

void Registry::removeEntityFromSystems(Entity entity) {
	for (auto& system : _systems) {
		system.second->removeEntityFromSystem(entity);
	}
}

void System::addEntity(Entity entity) { _entities.push_back(entity); }

void System::removeEntityFromSystem(Entity entity) {
	std::erase_if(_entities, [&entity](const Entity& other) { return other == entity; });
}