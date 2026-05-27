#pragma once

#include <raylib.h>

struct TransformComponent
{
    Vector2 Position;
};

struct VelocityComponent
{
    Vector2 Velocity;
};

struct RenderComponent
{
    int Width;
    int Height;

    Color Color;
};