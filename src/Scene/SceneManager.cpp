#include "Scene/SceneManager.hpp"

void SceneManager::ChangeScene(std::unique_ptr<Scene> newScene) {
	if (!scenes.empty()) {
		scenes.back()->CleanUp();
		scenes.pop_back();
	}

	scenes.push_back(std::move(newScene));
	scenes.back()->Init();
}

void SceneManager::PushScene(std::unique_ptr<Scene> newScene) {
	if (!scenes.empty()) {
		scenes.back()->Pause();
	}

	scenes.push_back(std::move(newScene));
	scenes.back()->Init();
}

void SceneManager::PopScene() {
	if (!scenes.empty()) {
		scenes.back()->CleanUp();
		scenes.pop_back();
	}

	if (!scenes.empty()) {
		scenes.back()->Resume();
	}
}

void SceneManager::HandleInput() {
	if (!scenes.empty()) {
		scenes.back()->HandleInput();
	}
}

void SceneManager::Update(float deltaTime) {
	if (!scenes.empty()) {
		scenes.back()->Update(deltaTime);
	}
}

void SceneManager::Render(GLFWwindow& window) {
	if (!scenes.empty()) {
		scenes.back()->Render(window);
	}
}