#pragma once

#include <raylib.h>
#include <vector>
#include <ecs/entities/wall.h>
#include <ecs/components/components.h>
#include <ecs/systems/movementsystem.h>
#include <ecs/systems/rendersystem.h>
#include <ecs/systems/rectanglecollisionsystem.h>

class Application
{
public:
    void Initialize();
    void Run();
    void Shutdown();

private:
    //Player
    TransformComponent m_PlayerTransform;
    VelocityComponent m_PlayerVelocity;
    RenderComponent m_PlayerRender;
    RectangleColliderComponent m_PlayerCollider;

    float m_PlayerSpeed = 300.0f;

    //Used systems
    MovementSystem m_MovementSystem;
    RenderSystem m_RenderSystem;
    RectangleCollisionSystem m_CollisionSystem;

    //Obstacles
    std::vector<Wall> m_Walls;

    void ProcessInput();
    void Update(float dt);
    void Render();
    void HandleCollisions(float dt);
};