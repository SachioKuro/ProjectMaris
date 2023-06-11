#pragma once

#include <array>
#include <cassert>
#include <memory>
#include <unordered_map>

#include "ECS/Components/Component.hpp"
#include "ECS/Components/ComponentArray.hpp"
#include "ECS/Entity/Entity.hpp"

using ComponentName = const char*;

class ComponentManager {
public:
	template<typename T>
	void RegisterComponent() {
		ComponentName componentName = typeid(T).name();

		assert(componentTypes.find(componentName) == componentTypes.end()
			&& "Registering component type more than once.");

		componentTypes.insert({ componentName, nextComponentType });
		componentArrays.insert({ componentName, std::make_shared<ComponentArray<T>>() });

		++nextComponentType;
	}

	template<typename T>
	ComponentType GetComponentType() {
		ComponentName componentName = typeid(T).name();

		assert(componentTypes.find(componentName) != componentTypes.end()
			&& "Component not registered before use.");

		return componentTypes[componentName];
	}

	template<typename T>
	void AddComponent(Entity entity, T component) {
		getComponentArray<T>()->InsertData(entity, component);
	}

	template<typename T>
	void RemoveComponent(Entity entity) {
		getComponentArray<T>()->RemoveData(entity);
	}

	template<typename T>
	T& GetComponent(Entity entity) {
		return getComponentArray<T>()->GetData(entity);
	}

	void EntityDestroyed(Entity entity) {
		for (auto const& [_, componentArray] : componentArrays) {
			if (componentArray)
				componentArray->EntityDestroyed(entity);
		}
	}
private:
	std::unordered_map<ComponentName, ComponentType> componentTypes{};
	std::unordered_map<ComponentName, std::shared_ptr<IComponentArray>> componentArrays;

	ComponentType nextComponentType{};

	template<typename T>
	std::shared_ptr<ComponentArray<T>> getComponentArray() {
		ComponentName componentName = typeid(T).name();

		assert(componentTypes.find(componentName) != componentTypes.end()
			&& "Component not registered before use.");

		return std::static_pointer_cast<ComponentArray<T>>(componentArrays[componentName]);
	}
};