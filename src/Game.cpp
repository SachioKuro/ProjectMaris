#include "Game.hpp"

#include <iostream>

#include "ECS/ECS.hpp"
#include "ECS/Entity/Entity.hpp"
#include "ECS/Components/Components.hpp";
#include "ECS/Systems/Systems.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

Game::Game() {
    m_window.Create(800, 600, "My Window");

    m_graphics.Initialize(&m_window);

    ecs = std::make_unique<ECS>();
    ecs->Init();

    ecs->RegisterComponent<PositionComponent>();
    ecs->RegisterComponent<VelocityComponent>();

    auto movementSystem = ecs->RegisterSystem<MovementSystem>(ecs.get());

    Signature signature;
    signature.set(ecs->GetComponentType<PositionComponent>(), true);
    signature.set(ecs->GetComponentType<VelocityComponent>(), true);
    ecs->SetSystemSignature<MovementSystem>(signature);

    Entity entity = ecs->CreateEntity();
    ecs->AddComponent(entity, PositionComponent{ 0.f, 0.f });
    ecs->AddComponent(entity, VelocityComponent{ 1.f, 1.5f });

    Entity entity2 = ecs->CreateEntity();
    ecs->AddComponent(entity2, PositionComponent{ 0.f, 0.f });
    ecs->AddComponent(entity2, VelocityComponent{ -1.5f, -1.f });
}

Game::~Game() {
    m_graphics.Finalize();
    m_window.Destroy();
}

void Game::run() {
    double timeSinceLastUpdate{};
    double TimePerFrame = 1./60.;

    while (m_window.IsOpen()) {
        processEvents();

        timeSinceLastUpdate += glfwGetTime();
        glfwSetTime(0);

        // Fixed time step loop
        // If the time since the last update is more than the time per frame, update and decrease the time since the last update
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame); // Update the game with a fixed timestep
        }

        render();
    }
}

void Game::processEvents() {
    m_window.PollEvents();
}

void Game::update(double deltaTime) {
    // Update the game state
    // In a full game, you would check for collisions, update animations, move sprites, etc.
    for (auto& [_, system] : ecs->GetSystems())
        system->Update(deltaTime);
}

void Game::render() {
    m_graphics.BeginFrame();
    m_graphics.Draw();
    m_graphics.EndFrame();
}