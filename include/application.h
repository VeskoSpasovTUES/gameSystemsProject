#pragma once

#include <raylib.h>

class Application
{
public:
    void Initialize();
    void Run();
    void Shutdown();

private:
    Vector2 m_position = {0.0f, 0.0f};
    float m_speed = 300.0f;

    void ProcessInput();
    void Update(float dt);
    void Render();
};