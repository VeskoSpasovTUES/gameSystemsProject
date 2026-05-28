#pragma once

#include <raylib.h>
#include <components.h>
#include <movementsystem.h>
#include <rendersystem.h>
#include <rectanglecollisionsystem.h>

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

    //Obstacle
    TransformComponent m_WallTransform;
    RectangleColliderComponent m_WallCollider;
    RenderComponent m_WallRender;

    //Debug variables
    Vector2 m_DebugContactPoint = { 0,0 };
    bool m_Hit = false;

    void ProcessInput();
    void Update(float dt);
    void Render();
};