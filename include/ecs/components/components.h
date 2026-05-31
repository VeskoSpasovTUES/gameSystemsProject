#pragma once

#include <raylib.h>
#include <string>

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

struct RectangleColliderComponent 
{
    Vector2 Size;
};

struct SpriteComponent
{
    std::string TextureId;

    float Rotation = 0.0f;
    float Scale = 1.0f;
};