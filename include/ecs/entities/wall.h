#pragma once

#include <ecs/components/components.h>

struct Wall
{
    TransformComponent Transform;
    RectangleColliderComponent Collider;
    RenderComponent Render;
};