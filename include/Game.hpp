#pragma once

#include <memory>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Graphics/GLFWWindow.hpp"
#include "Graphics/VulkanGraphics.hpp"
#include "ECS/ECS.hpp"

class Game {
public:
    Game();
    ~Game();
    void run();
    void processEvents();
    void update(double deltaTime);
    void render();

private:
    GLFWWindow m_window{};
    VulkanGraphics m_graphics{};

    std::unique_ptr<ECS> ecs;
};