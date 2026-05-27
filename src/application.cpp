#include "application.h"
#include "input.h"

#include <raylib.h>

void Application::Initialize()
{
    const int window_width = 1280;
    const int window_height = 720;

    m_PlayerTransform.Position = {100.0f, 100.0f};

    m_PlayerVelocity.Velocity = {0.0f, 0.0f};

    m_PlayerRender.Width = 50;
    m_PlayerRender.Height = 50;
    m_PlayerRender.Color = GREEN;

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

    m_MovementSystem.Update(m_PlayerTransform, m_PlayerVelocity, dt);
}

void Application::Render()
{
    BeginDrawing();

    ClearBackground(BLACK);

    m_RenderSystem.Render(m_PlayerTransform, m_PlayerRender);

    DrawFPS(10, 10);

    EndDrawing();
}