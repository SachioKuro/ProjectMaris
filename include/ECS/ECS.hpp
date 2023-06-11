#pragma once

#include <memory>

#include "ECS/Components/ComponentManager.hpp"
#include "ECS/Entity/EntityManager.hpp"
#include "ECS/Systems/SystemManager.hpp"

class ECS {
public:
	ECS() = default;

	void Init() {
		entityManager = std::make_unique<EntityManager>();
		componentManager = std::make_unique<ComponentManager>();
		systemManager = std::make_unique<SystemManager>();
	}

	Entity CreateEntity() {
		return entityManager->CreateEntity();
	}

	void DestroyEntity(Entity entity) {
		entityManager->DestroyEntity(entity);
		componentManager->EntityDestroyed(entity);
		systemManager->EntityDestroyed(entity);
	}

	template<typename T>
	void RegisterComponent() {
		componentManager->RegisterComponent<T>();
	}

	template<typename T>
	void AddComponent(Entity entity, T component) {
		componentManager->AddComponent<T>(entity, component);

		auto signature = entityManager->GetSignature(entity);
		signature.set(componentManager->GetComponentType<T>(), true);
		entityManager->SetSignature(entity, signature);

		systemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& GetComponent(Entity entity) const {
		return componentManager->GetComponent<T>(entity);
	}

	template<typename T>
	ComponentType GetComponentType() {
		return componentManager->GetComponentType<T>();
	}

	template<typename T>
	std::shared_ptr<T> RegisterSystem(const ECS* ecs) {
		return systemManager->RegisterSystem<T>(ecs);
	}

	template<typename T>
	void SetSystemSignature(Signature signature) {
		systemManager->SetSignature<T>(signature);
	}

	auto GetSystems() {
		return systemManager->GetSystems();
	}
private:
	std::unique_ptr<EntityManager> entityManager;
	std::unique_ptr<ComponentManager> componentManager;
	std::unique_ptr<SystemManager> systemManager;
};