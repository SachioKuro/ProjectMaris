#pragma once

#include <array>
#include <cassert>
#include <unordered_map>

#include "ECS/Entity/Entity.hpp"

class IComponentArray {
public:
    virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray {
public:
    void InsertData(Entity entity, T component) {
        assert(entityToIndexMap.find(entity) == entityToIndexMap.end()
            && "Component added to same entity more than once.");

        entityToIndexMap[entity] = size;
        indexToEntityMap[size] = entity;
        componentArray[size] = component;
        ++size;
    }

    void RemoveData(Entity entity) {
        assert(entityToIndexMap.find(entity) != entityToIndexMap.end()
            && "Removing non-existent component.");

        auto indexOfRemovedEntity = entityToIndexMap[entity];
        auto indexOfLastElement = size - 1;
        componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];

        auto lastEntity = indexToEntityMap[indexOfLastElement];
        entityToIndexMap[lastEntity] = indexOfRemovedEntity;
        indexToEntityMap[indexOfRemovedEntity] = lastEntity;

        entityToIndexMap.erase(entity);
        indexToEntityMap.erase(indexOfLastElement);

        --size;
    }

    T& GetData(Entity entity) {
        assert(entityToIndexMap.find(entity) != entityToIndexMap.end()
            && "Retrieving non-existent component.");

        return componentArray[entityToIndexMap[entity]];
    }

    void EntityDestroyed(Entity entity) override {
        if (entityToIndexMap.find(entity) != entityToIndexMap.end()) {
            RemoveData(entity);
        }
    }
private:
	// The packed array that contains the components, indexed by an entity index
    std::array<T, MAX_ENTITIES> componentArray{};

    // Map from an entity to an index
    std::unordered_map<Entity, size_t> entityToIndexMap{};

    // Map from an index to an entity
    std::unordered_map<size_t, Entity> indexToEntityMap{};

    // Total size of valid entries in the array
    EntityType size;
};