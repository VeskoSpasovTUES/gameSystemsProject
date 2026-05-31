#pragma once

#include <raylib.h>
#include <scene/scene.h>
#include <ecs/systems/movementsystem.h>
#include <ecs/systems/rendersystem.h>
#include <ecs/systems/rectanglecollisionsystem.h>
#include <resources/resourcemanager.h>

class Application
{
public:
    void Initialize();
    void Run();
    void Shutdown();

private:
    float m_PlayerSpeed = 300.0f;

    float WORLD_WIDTH = 5000.0f;
    float WORLD_HEIGHT = 5000.0f;

    bool m_ShowColliders = true;

    Scene m_Scene;
    Camera2D m_Camera;

    MovementSystem m_MovementSystem;
    RenderSystem m_RenderSystem;
    RectangleCollisionSystem m_CollisionSystem;

    ResourceManager m_ResourceManager;

    void ProcessInput();
    void Update(float dt);
    void UpdateCamera();
    void Render();
    void RenderGame();
    void RenderDebugUI();
    void HandleCollisions(float dt);
};