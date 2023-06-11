#pragma once

#include <memory>
#include <vector>
#include <GLFW/glfw3.h>

#include "Scene/Scene.hpp"

class SceneManager {
public:
    void ChangeScene(std::unique_ptr<Scene> newScene);
    void PushScene(std::unique_ptr<Scene> newScene);
    void PopScene();

    void HandleInput();
    void Update(float deltaTime);
    void Render(GLFWwindow& window);

private:
    std::vector<std::unique_ptr<Scene>> scenes;
};