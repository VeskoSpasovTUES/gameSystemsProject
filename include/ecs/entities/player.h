#pragma once

#include "ecs/components/components.h"

struct Player
{
    TransformComponent Transform;
    VelocityComponent Velocity;
    RenderComponent Render;
    RectangleColliderComponent Collider;
};