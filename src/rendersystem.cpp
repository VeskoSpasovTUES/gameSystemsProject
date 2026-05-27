#include "RenderSystem.h"

#include <raylib.h>

void RenderSystem::Render(const TransformComponent& transform, const RenderComponent& render)
{
    DrawRectangle((int)transform.Position.x, (int)transform.Position.y, render.Width, render.Height, render.Color);
}