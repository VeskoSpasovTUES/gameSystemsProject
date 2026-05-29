#include "core/application.h"
#include "core/input.h"

#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <algorithm>

void Application::Initialize()
{
    //Initialize player
    m_PlayerTransform.Position = {100.0f, 100.0f};

    m_PlayerVelocity.Velocity = {0.0f, 0.0f};

    m_PlayerRender.Width = 50;
    m_PlayerRender.Height = 50;
    m_PlayerRender.Color = GREEN;

    m_PlayerCollider.Size = { 50.0f, 50.0f };

    //Initialize wall1
    Wall wall1;

    wall1.Transform.Position = { 500, 200 };

    wall1.Collider.Size = { 100, 300 };

    wall1.Render.Width = 100;
    wall1.Render.Height = 300;
    wall1.Render.Color = RED;

    m_Walls.push_back(wall1);

    //Initialize wall2
    Wall wall2;

    wall2.Transform.Position = { 200, 500 };

    wall2.Collider.Size = { 400, 50 };

    wall2.Render.Width = 400;
    wall2.Render.Height = 50;
    wall2.Render.Color = BLUE;

    m_Walls.push_back(wall2);

    //Initialize wall3
    Wall wall3;

    wall3.Transform.Position = { 250, 400 };

    wall3.Collider.Size = { 350, 50 };

    wall3.Render.Width = 350;
    wall3.Render.Height = 50;
    wall3.Render.Color = BLUE;

    m_Walls.push_back(wall3);

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

    //Check for collisions and resolve them
    HandleCollisions(dt);
}

void Application::Render()
{
    BeginDrawing();

    ClearBackground(BLACK);

    m_RenderSystem.Render(m_PlayerTransform, m_PlayerRender);
    for (const Wall& wall : m_Walls)
    {
        m_RenderSystem.Render(
            wall.Transform,
            wall.Render
        );
    }

    DrawFPS(10, 10);

    EndDrawing();
}

void Application::HandleCollisions(float dt) 
{
    float remainingTime = dt;

    for (int iteration = 0; iteration < 2; iteration++)
    {
        Vector2 contactPoint;
        Vector2 contactNormal;

        float nearestHitTime = 1.0f;

        int nearestWall = -1;

        for (int i = 0; i < m_Walls.size(); i++)
        {
            float hitTime;

            bool hit = m_CollisionSystem.DynamicRectangleVsRectangle(m_PlayerTransform, m_PlayerCollider, m_PlayerVelocity, m_Walls[i].Transform, m_Walls[i].Collider, contactPoint, contactNormal, hitTime, remainingTime);

            if (hit)
            {
                if (hitTime < nearestHitTime)
                {
                    nearestHitTime = hitTime;
                    nearestWall = i;
                }
            }
        }

        if (nearestWall >= 0)
        {
            Vector2 finalContactPoint;
            Vector2 finalContactNormal;

            float finalHitTime;

            m_CollisionSystem.DynamicRectangleVsRectangle(m_PlayerTransform, m_PlayerCollider, m_PlayerVelocity, m_Walls[nearestWall].Transform, m_Walls[nearestWall].Collider, finalContactPoint, finalContactNormal, finalHitTime, remainingTime);

            m_CollisionSystem.ResolveDynamicRectangleVsRectangle(m_PlayerTransform, m_PlayerVelocity, finalContactNormal, finalHitTime, remainingTime);

            remainingTime *= (1.0f - finalHitTime);
        }
        else
        {
            m_MovementSystem.Update(m_PlayerTransform, m_PlayerVelocity, remainingTime);
            break;
        }
    }
}