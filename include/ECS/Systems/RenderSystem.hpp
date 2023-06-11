#pragma once

#include <GLFW/glfw3.h>

#include "ECS/Systems/System.hpp"
#include "ECS/Components/ComponentArray.hpp"
#include "ECS/Components/RenderComponent.hpp"

class RenderSystem : public ISystem {
public:
    void update(GLFWwindow& window, ComponentArray<RenderComponent>& renderComponents) {
        for (auto const& entity : entities) {
            auto& component = renderComponents.GetData(entity);
            // Draw the entity using the component data and the SFML window...
        }
    }
};