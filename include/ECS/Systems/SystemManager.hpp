#pragma once

#include <cassert>
#include <memory>
#include <unordered_map>

#include "ECS/Systems/System.hpp"
#include "ECS/Components/Component.hpp"
#include "ECS/Entity/Entity.hpp"

class ECS;

using SystemName = const char*;

class SystemManager {
public:
	template<typename T>
	std::shared_ptr<T> RegisterSystem(const ECS* ecs) {
		SystemName systemName = typeid(T).name();

		assert(systems.find(systemName) == systems.end()
			&& "Registering system more than once.");

		auto system = std::make_shared<T>(ecs);
		systems.insert({ systemName, system });
		return system;
	}

	template<typename T>
	void SetSignature(Signature signature) {
		SystemName systemName = typeid(T).name();

		assert(systems.find(systemName) != systems.end()
			&& "System used before registered.");

		signatures.insert({ systemName, signature });
	}

	auto GetSystems() {
		return systems;
	}

	void EntityDestroyed(Entity entity) {
		for (auto const& [_, system] : systems) {
			system->GetEntities().erase(entity);
		}
	}

	void EntitySignatureChanged(Entity entity, Signature newSignature) {
		for (auto const& [systemName, system] : systems) {
			auto const& systemSignature = signatures[systemName];

			if ((newSignature & systemSignature) == systemSignature)
				system->GetEntities().insert(entity);
			else
				system->GetEntities().erase(entity);
		}
	}
private:
	std::unordered_map<SystemName, Signature> signatures;
	std::unordered_map<SystemName, std::shared_ptr<ISystem>> systems;
};