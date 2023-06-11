#include "Graphics/GLFWWindow.hpp"

void GLFWWindow::Create(uint16_t width, uint16_t height, const std::string& title) {
	m_width = width;
	m_height = height;
	m_title = title;

	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
	glfwSetWindowUserPointer(m_window, this);
	glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);
}

void GLFWWindow::Destroy() {
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool GLFWWindow::IsOpen() const {
	return !glfwWindowShouldClose(m_window);
}

void GLFWWindow::Close() {
	glfwSetWindowShouldClose(m_window, GLFW_FALSE);
}

void GLFWWindow::PollEvents() {
	glfwPollEvents();
}

void GLFWWindow::Display() {

}

void GLFWWindow::Clear() {

}

void GLFWWindow::SetTitle(const std::string& title) {
	glfwSetWindowTitle(m_window, title.c_str());
}

void GLFWWindow::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
	auto app_window = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
	app_window->SetResized();
}