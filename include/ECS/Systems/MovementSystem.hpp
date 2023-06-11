#pragma once

#include <iostream>

#include "ECS/ECS.hpp"
#include "ECS/Systems/System.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"


class MovementSystem : public ISystem {
public:
	using ISystem::ISystem;
	void Update(float dt) override {
		for (auto const& entity : entities) {
			auto& position = ecs->GetComponent<PositionComponent>(entity);
			auto& velocity = ecs->GetComponent<VelocityComponent>(entity);

			position.x += velocity.dx * dt;
			position.y += velocity.dy * dt;

			// std::cout << "New position: " << position.x << " - " << position.y << std::endl;
		}
	}
};