#pragma once

#include "ecs/components/Components.h"

class RenderSystem
{
public:
    void Render(const TransformComponent& transform, const RenderComponent& render);
};