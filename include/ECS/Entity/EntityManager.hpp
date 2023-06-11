#pragma once

#include <array>
#include <cassert>
#include <queue>

#include "ECS/Entity/Entity.hpp"
#include "ECS/Components/Component.hpp"

class EntityManager {
public:
	EntityManager() {
		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
			availableEntities.push(entity);
	}

	Entity CreateEntity() {
		assert(livingEntityCount < MAX_ENTITIES
			&& "Too many entities in existence.");

		Entity entity = availableEntities.front();
		availableEntities.pop();
		++livingEntityCount;

		return entity;
	}

	void DestroyEntity(Entity entity) {
		assert(entity < MAX_ENTITIES
			&& "Entity out of range.");

		signatures[entity].reset();

		availableEntities.push(entity);
		--livingEntityCount;
	}

	void SetSignature(Entity entity, Signature signature) {
		assert(entity < MAX_ENTITIES
			&& "Entity out of range.");

		signatures[entity] = signature;
	}

	Signature GetSignature(Entity entity) {
		assert(entity < MAX_ENTITIES
			&& "Entity out of range.");

		return signatures[entity];
	}
private:
	// good default choice for storing available IDs
	std::queue<Entity> availableEntities{};
	std::array<Signature, MAX_COMPONENTS> signatures{};
	EntityType livingEntityCount{};
};