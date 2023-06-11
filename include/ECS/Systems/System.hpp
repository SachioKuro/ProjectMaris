#pragma once

#include <cstdint>
#include <unordered_set>

#include "ECS/Entity/Entity.hpp"


class ECS;

using SystemType = std::uint8_t;
const SystemType MAX_SYSTEMS = 32;

class ISystem {
public:
	ISystem(const ECS* ecs): ecs(ecs) {}

	std::unordered_set<Entity>& GetEntities() {
		return entities;
	}

	virtual void Update(float dt) = 0;
protected:
	const ECS* ecs;
	std::unordered_set<Entity> entities;
};