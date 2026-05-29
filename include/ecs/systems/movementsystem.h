#pragma once

#include "ecs/components/Components.h"

class MovementSystem
{
public:
    void Update(TransformComponent& transform, VelocityComponent& velocity, float dt);
};