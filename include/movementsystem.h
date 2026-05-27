#pragma once

#include "Components.h"

class MovementSystem
{
public:
    void Update(TransformComponent& transform, VelocityComponent& velocity, float dt);
};