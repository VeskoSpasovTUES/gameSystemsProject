#pragma once

#include "ecs/components/Components.h"

class RenderSystem
{
public:
    void Render(const TransformComponent& transform, const RenderComponent& render);
    void Render(const TransformComponent& transform, const RectangleColliderComponent& collider, const SpriteComponent& sprite, const Texture2D& texture);
};