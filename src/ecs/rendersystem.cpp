#include "ecs/systems/RenderSystem.h"

#include <raylib.h>

void RenderSystem::Render(const TransformComponent& transform, const RenderComponent& render)
{
    DrawRectangle((int)transform.Position.x - render.Width * 0.5f, (int)transform.Position.y - render.Height * 0.5f, render.Width, render.Height, render.Color);
}

void RenderSystem::Render(const TransformComponent& transform, const RectangleColliderComponent& collider, const SpriteComponent& sprite, const Texture2D& texture)
{
    Rectangle sourceRect = {0.0f, 0.0f, (float)texture.width, (float)texture.height};

    Rectangle destRect = {transform.Position.x, transform.Position.y, collider.Size.x, collider.Size.y};

    Vector2 origin = {collider.Size.x * 0.5f, collider.Size.y * 0.5f};

    DrawTexturePro(texture, sourceRect, destRect, origin, sprite.Rotation, WHITE);
}