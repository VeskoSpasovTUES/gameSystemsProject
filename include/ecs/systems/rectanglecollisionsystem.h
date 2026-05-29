#pragma once

#include "ecs/components/Components.h"

class RectangleCollisionSystem
{
public:
    bool RayVsRectangle(const Vector2& rayOrigin, const Vector2& rayDirection, const TransformComponent& targetTransform, const RectangleColliderComponent& targetCollider, Vector2& contactPoint, Vector2& contactNormal, float& hitTime);
    bool DynamicRectangleVsRectangle(const TransformComponent& dynamicTransform, const RectangleColliderComponent& dynamicCollider, const VelocityComponent& dynamicVelocity,const TransformComponent& targetTransform, const RectangleColliderComponent& targetCollider, Vector2& contactPoint, Vector2& contactNormal, float& hitTime, const float& dt);
    void ResolveDynamicRectangleVsRectangle(TransformComponent& dynamicTransform, VelocityComponent& dynamicVelocity, const Vector2& contactNormal, float hitTime, float dt);
};