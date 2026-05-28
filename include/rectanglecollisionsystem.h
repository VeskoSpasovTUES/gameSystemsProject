#pragma once

#include "Components.h"

class RectangleCollisionSystem
{
public:
    bool RayVsRectangle(const Vector2& rayOrigin, const Vector2& rayDirection, const TransformComponent& targetTransform, const RectangleColliderComponent& targetCollider, Vector2& contactPoint, Vector2& contactNormal, float& hitTime);
};