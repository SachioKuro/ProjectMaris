#pragma once

#include <GLFW/glfw3.h>

class Scene {
public:
    virtual ~Scene() = default;

    virtual void Init() = 0;
    virtual void CleanUp() = 0;

    virtual void Pause() = 0;
    virtual void Resume() = 0;

    virtual void HandleInput() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render(GLFWwindow& window) = 0;
};