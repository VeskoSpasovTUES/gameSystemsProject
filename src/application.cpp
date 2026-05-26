#include "application.h"
#include "input.h"

#include <raylib.h>

void Application::Initialize()
{
    const int window_width = 1280;
    const int window_height = 720;

    InitWindow(window_width, window_height, "Game");
    SetTargetFPS(360);
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
    if (Input::IsKeyDown(KEY_W))
    {
        m_position.y -= m_speed * dt;
    }
    if (Input::IsKeyDown(KEY_A))
    {
        m_position.x -= m_speed * dt;
    }
    if (Input::IsKeyDown(KEY_S))
    {
        m_position.y += m_speed * dt;
    }
    if (Input::IsKeyDown(KEY_D))
    {
        m_position.x += m_speed * dt;
    }
    if (m_position.x < 0)
    {
        m_position.x = 0;
    }

    if (m_position.x > 1230)
    {
        m_position.x = 1230;
    }

    if (m_position.y < 0)
    {
        m_position.y = 0;
    }

    if (m_position.y > 670)
    {
        m_position.y = 670;
    }
}

void Application::Render()
{
    BeginDrawing();

    ClearBackground(BLACK);

    DrawRectangle((int)m_position.x, (int)m_position.y, 50, 50, GREEN);

    DrawFPS(10, 10);

    EndDrawing();
}