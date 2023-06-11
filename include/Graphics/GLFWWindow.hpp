#pragma once

#include "Graphics/Window.hpp"

#include <GLFW/glfw3.h>

class GLFWWindow : public IWindow {
public:
    virtual ~GLFWWindow() = default;

    virtual void Create(uint16_t width, uint16_t height, const std::string& title);
    virtual void Destroy();

    virtual bool IsOpen() const;
    virtual void Close();

    virtual void PollEvents();

    virtual void Display();
    virtual void Clear();

    virtual void SetTitle(const std::string& title);

    virtual void* GetWindowObj() { return m_window; }
private:
    GLFWwindow* m_window;

    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
};