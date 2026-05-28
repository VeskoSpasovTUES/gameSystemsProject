#include "application.h"
#include "input.h"

#include <raylib.h>
#include <raymath.h>
#include <iostream>

void Application::Initialize()
{
    //Initialize player
    m_PlayerTransform.Position = {100.0f, 100.0f};

    m_PlayerVelocity.Velocity = {0.0f, 0.0f};

    m_PlayerRender.Width = 50;
    m_PlayerRender.Height = 50;
    m_PlayerRender.Color = GREEN;

    m_PlayerCollider.Size = { 50.0f, 50.0f };

    //Initialize wall
    m_WallTransform.Position = { 500.0f, 200.0f };

    m_WallCollider.Size = { 100.0f, 300.0f };

    m_WallRender.Width = 100;
    m_WallRender.Height = 300;
    m_WallRender.Color = RED;

    //Initialize window
    const int window_width = 1280;
    const int window_height = 720;

    InitWindow(window_width, window_height, "Game");
    SetTargetFPS(60);
}

void Application::Run()
{
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        ProcessInput();
        Update(dt);
        Render();
    }
}

void Application::Shutdown()
{
    CloseWindow();
}

void Application::ProcessInput()
{
}

void Application::Update(float dt)
{
    m_PlayerVelocity.Velocity = { 0.0f, 0.0f };

    if (Input::IsKeyDown(KEY_W))
    {
        m_PlayerVelocity.Velocity.y = -m_PlayerSpeed;
    }

    if (Input::IsKeyDown(KEY_S))
    {
        m_PlayerVelocity.Velocity.y = m_PlayerSpeed;
    }

    if (Input::IsKeyDown(KEY_A))
    {
        m_PlayerVelocity.Velocity.x = -m_PlayerSpeed;
    }

    if (Input::IsKeyDown(KEY_D))
    {
        m_PlayerVelocity.Velocity.x = m_PlayerSpeed;
    }

    Vector2 contactPoint;
    Vector2 contactNormal;

    float hitTime;

    bool hit = m_CollisionSystem.RayVsRectangle(m_PlayerTransform.Position, Vector2Scale(m_PlayerVelocity.Velocity, dt), m_WallTransform, m_WallCollider, contactPoint, contactNormal, hitTime);

    m_Hit = hit;

    if (hit) m_DebugContactPoint = contactPoint;

    if (!hit) m_MovementSystem.Update(m_PlayerTransform, m_PlayerVelocity, dt);
}

void Application::Render()
{
    BeginDrawing();

    ClearBackground(BLACK);

    m_RenderSystem.Render(m_PlayerTransform, m_PlayerRender);
    m_RenderSystem.Render(m_WallTransform, m_WallRender);

    if (m_Hit) DrawCircle((int)m_DebugContactPoint.x, (int)m_DebugContactPoint.y, 5, YELLOW);

    DrawFPS(10, 10);

    EndDrawing();
}