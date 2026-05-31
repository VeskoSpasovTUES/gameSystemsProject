#include "core/application.h"
#include "core/input.h"

#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <algorithm>
#include <imgui.h>
#include <rlImGui.h>

void Application::Initialize()
{
    //Initialize window
    const int window_width = 1280;
    const int window_height = 720;

    InitWindow(window_width, window_height, "Game");
    SetTargetFPS(60);

    rlImGuiSetup(true);

    //Load Textures
    m_ResourceManager.LoadTextureResource("rabbit", RESOURCES_PATH "rabbit.png");

    //Initialize player
    m_Scene.Player.Transform.Position = {300.0f, 250.0f};

    m_Scene.Player.Velocity.Velocity = {0.0f, 0.0f};

    m_Scene.Player.Render.Width = 50;
    m_Scene.Player.Render.Height = 50;
    m_Scene.Player.Render.Color = GREEN;

    m_Scene.Player.Collider.Size = { 50.0f, 50.0f };

    m_Scene.Player.Sprite.TextureId = "rabbit";

    //Initialize wall1
    Wall wall1;

    wall1.Transform.Position = { 550, 350 };

    wall1.Collider.Size = { 100, 300 };

    wall1.Render.Width = 100;
    wall1.Render.Height = 300;
    wall1.Render.Color = RED;

    m_Scene.Walls.push_back(wall1);

    //Initialize wall2
    Wall wall2;

    wall2.Transform.Position = { 400, 525 };

    wall2.Collider.Size = { 400, 50 };

    wall2.Render.Width = 400;
    wall2.Render.Height = 50;
    wall2.Render.Color = BLUE;

    m_Scene.Walls.push_back(wall2);

    //Initialize wall3
    Wall wall3;

    wall3.Transform.Position = { 425, 425 };

    wall3.Collider.Size = { 350, 50 };

    wall3.Render.Width = 350;
    wall3.Render.Height = 50;
    wall3.Render.Color = BLUE;

    m_Scene.Walls.push_back(wall3);

    //Initialize camera
    m_Camera.target = m_Scene.Player.Transform.Position;
    m_Camera.offset = { 640.0f, 360.0f };
    m_Camera.rotation = 0.0f;
    m_Camera.zoom = 1.0f;
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
    rlImGuiShutdown();

    CloseWindow();
}

void Application::ProcessInput()
{
}

void Application::Update(float dt)
{
    m_Scene.Player.Velocity.Velocity = { 0.0f, 0.0f };

    if (Input::IsKeyDown(KEY_W))
    {
        m_Scene.Player.Velocity.Velocity.y = -m_PlayerSpeed;
    }

    if (Input::IsKeyDown(KEY_S))
    {
        m_Scene.Player.Velocity.Velocity.y = m_PlayerSpeed;
    }

    if (Input::IsKeyDown(KEY_A))
    {
        m_Scene.Player.Velocity.Velocity.x = -m_PlayerSpeed;
    }

    if (Input::IsKeyDown(KEY_D))
    {
        m_Scene.Player.Velocity.Velocity.x = m_PlayerSpeed;
    }

    HandleCollisions(dt);

    UpdateCamera();
}

void Application::UpdateCamera()
{
    m_Camera.target.x = m_Scene.Player.Transform.Position.x + m_Scene.Player.Render.Width * 0.5f;
    m_Camera.target.y = m_Scene.Player.Transform.Position.y + m_Scene.Player.Render.Height * 0.5f;

    float visibleWidth = GetScreenWidth() / m_Camera.zoom;
    float visibleHeight = GetScreenHeight() / m_Camera.zoom;

    float halfWidth = visibleWidth * 0.5f;
    float halfHeight = visibleHeight * 0.5f;

    m_Camera.target.x = std::clamp(m_Camera.target.x, halfWidth, WORLD_WIDTH - halfWidth);
    m_Camera.target.y = std::clamp(m_Camera.target.y, halfHeight, WORLD_HEIGHT - halfHeight);
}

void Application::Render()
{
    BeginDrawing();

    ClearBackground(BLACK);

    BeginMode2D(m_Camera);
    RenderGame();
    EndMode2D();

    rlImGuiBegin();
    RenderDebugUI();
    rlImGuiEnd();

    EndDrawing();
}

void Application::RenderGame()
{
    Texture2D& playerTexture = m_ResourceManager.GetTexture(m_Scene.Player.Sprite.TextureId);
    m_RenderSystem.Render(m_Scene.Player.Transform, m_Scene.Player.Collider, m_Scene.Player.Sprite, playerTexture);

    for (const Wall& wall : m_Scene.Walls)
    {
        m_RenderSystem.Render(wall.Transform, wall.Render);
    }

    //Debug outlines
    if(m_ShowColliders) 
    {
        DrawRectangleLines(0, 0, (int)WORLD_WIDTH, (int)WORLD_HEIGHT, YELLOW);
        DrawRectangleLines((int)m_Scene.Player.Transform.Position.x - (int)m_Scene.Player.Collider.Size.x * 0.5f, (int)m_Scene.Player.Transform.Position.y - (int)m_Scene.Player.Collider.Size.y * 0.5f, (int)m_Scene.Player.Collider.Size.x, (int)m_Scene.Player.Collider.Size.y, YELLOW);
        for (const Wall& wall : m_Scene.Walls)
        {
            DrawRectangleLines((int)wall.Transform.Position.x - (int)wall.Collider.Size.x * 0.5f, (int)wall.Transform.Position.y - (int)wall.Collider.Size.y * 0.5f, (int)wall.Collider.Size.x, (int)wall.Collider.Size.y, YELLOW);
        }
    }
}

void Application::RenderDebugUI()
{
    ImGui::Begin("Debug");

    ImGui::Text("FPS: %d", GetFPS());

    ImGui::Separator();

    ImGui::Text("Position: %.2f %.2f", m_Scene.Player.Transform.Position.x, m_Scene.Player.Transform.Position.y);
    ImGui::Text("Velocity: %.2f %.2f", m_Scene.Player.Velocity.Velocity.x, m_Scene.Player.Velocity.Velocity.y);

    ImGui::Separator();

    ImGui::Text("Camera Target: %.2f %.2f", m_Camera.target.x, m_Camera.target.y);
    ImGui::Text("Camera Zoom: %.2f", m_Camera.zoom);

    ImGui::Separator();

    ImGui::Text("Walls: %d", (int)m_Scene.Walls.size());

    ImGui::Separator();

    ImGui::SliderFloat("Player Speed", &m_PlayerSpeed, 50.0f, 1000.0f);
    ImGui::SliderFloat("Camera Zoom", &m_Camera.zoom, 0.5f, 4.0f);

    ImGui::Separator();

    ImGui::Checkbox("Show Colliders", &m_ShowColliders);

    ImGui::End();
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

        for (int i = 0; i < m_Scene.Walls.size(); i++)
        {
            float hitTime;

            bool hit = m_CollisionSystem.DynamicRectangleVsRectangle(m_Scene.Player.Transform, m_Scene.Player.Collider, m_Scene.Player.Velocity, m_Scene.Walls[i].Transform, m_Scene.Walls[i].Collider, contactPoint, contactNormal, hitTime, remainingTime);

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

            m_CollisionSystem.DynamicRectangleVsRectangle(m_Scene.Player.Transform, m_Scene.Player.Collider, m_Scene.Player.Velocity, m_Scene.Walls[nearestWall].Transform, m_Scene.Walls[nearestWall].Collider, finalContactPoint, finalContactNormal, finalHitTime, remainingTime);

            m_CollisionSystem.ResolveDynamicRectangleVsRectangle(m_Scene.Player.Transform, m_Scene.Player.Velocity, finalContactNormal, finalHitTime, remainingTime);

            remainingTime *= (1.0f - finalHitTime);
        }
        else
        {
            m_MovementSystem.Update(m_Scene.Player.Transform, m_Scene.Player.Velocity, remainingTime);
            break;
        }
    }
}