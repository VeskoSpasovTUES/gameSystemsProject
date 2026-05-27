#pragma once

#include <raylib.h>
#include <components.h>
#include <movementsystem.h>
#include <rendersystem.h>

class Application
{
public:
    void Initialize();
    void Run();
    void Shutdown();

private:
    TransformComponent m_PlayerTransform;
    VelocityComponent m_PlayerVelocity;
    RenderComponent m_PlayerRender;

    float m_PlayerSpeed = 300.0f;

    MovementSystem m_MovementSystem;
    RenderSystem m_RenderSystem;

    void ProcessInput();
    void Update(float dt);
    void Render();
};