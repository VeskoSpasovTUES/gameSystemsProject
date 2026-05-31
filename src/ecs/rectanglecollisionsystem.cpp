#include "ecs/systems/rectanglecollisionsystem.h"
#include <raymath.h>
#include <cmath>
#include <algorithm>

bool RectangleCollisionSystem::RayVsRectangle(const Vector2& rayOrigin, const Vector2& rayDirection, const TransformComponent& targetTransform, const RectangleColliderComponent& targetCollider, Vector2& contactPoint, Vector2& contactNormal, float& hitTimeNear)
{
	contactPoint = { 0,0 };
	contactNormal = { 0,0 };

	Vector2 rectTopLeft = {targetTransform.Position.x - targetCollider.Size.x * 0.5f, targetTransform.Position.y - targetCollider.Size.y * 0.5f};
	Vector2 rectTopRight = { targetTransform.Position.x + targetCollider.Size.x * 0.5f, targetTransform.Position.y + targetCollider.Size.y * 0.5f };

	Vector2 direction = rayDirection;

	Vector2 nearVector = Vector2Divide(Vector2Subtract(rectTopLeft, rayOrigin), direction);
	Vector2 farVector = Vector2Divide(Vector2Subtract(rectTopRight, rayOrigin), direction);

	if (std::isnan(nearVector.y) || std::isnan(nearVector.x)) return false;
	if (std::isnan(farVector.y) || std::isnan(farVector.x)) return false;

	if (nearVector.x > farVector.x) std::swap(nearVector.x, farVector.x);
	if (nearVector.y > farVector.y) std::swap(nearVector.y, farVector.y);

	if (nearVector.x > farVector.y || nearVector.y > farVector.x) return false;

	hitTimeNear = std::max(nearVector.x, nearVector.y);

	float hitTimeFar = std::min(farVector.x, farVector.y);

	if (hitTimeFar < 0) return false;

	if (hitTimeNear > 1) return false;

	contactPoint = Vector2Add(rayOrigin, Vector2Scale(direction, hitTimeNear));

	if (nearVector.x > nearVector.y)
		if (direction.x > 0)
			contactNormal = { -1, 0 };
		else
			contactNormal = { 1, 0 };
	else if (nearVector.x < nearVector.y)
		if (direction.y > 0)
			contactNormal = { 0, -1 };
		else
			contactNormal = { 0, 1 };

	return true;
}

bool RectangleCollisionSystem::DynamicRectangleVsRectangle(const TransformComponent& dynamicTransform, const RectangleColliderComponent& dynamicCollider, const VelocityComponent& dynamicVelocity, const TransformComponent& targetTransform, const RectangleColliderComponent& targetCollider, Vector2& contactPoint, Vector2& contactNormal, float& hitTime, const float& dt)
{
	//Assuming rectangles are NOT colliding at the start
	if (dynamicVelocity.Velocity.x == 0 && dynamicVelocity.Velocity.y == 0) return false;

	TransformComponent expandedTargetTransform; 
	expandedTargetTransform.Position = targetTransform.Position;

	RectangleColliderComponent expandedTargetCollider;
	expandedTargetCollider.Size = Vector2Add(targetCollider.Size, dynamicCollider.Size);

	Vector2 rayOrigin = dynamicTransform.Position;

	if (RayVsRectangle(rayOrigin, Vector2Scale(dynamicVelocity.Velocity, dt), expandedTargetTransform, expandedTargetCollider, contactPoint, contactNormal, hitTime))
		return (hitTime >= 0.0f && hitTime <= 1.0f);
	else 
		return false;
}

void RectangleCollisionSystem::ResolveDynamicRectangleVsRectangle(TransformComponent& dynamicTransform, VelocityComponent& dynamicVelocity, const Vector2& contactNormal, float hitTime, float dt) 
{
	//Apply movement until collision
	Vector2 movement = Vector2Scale(dynamicVelocity.Velocity, dt);
	dynamicTransform.Position = Vector2Add(dynamicTransform.Position, Vector2Scale(movement, hitTime));

	if (contactNormal.x != 0.0f) dynamicVelocity.Velocity.x = 0.0f;
	if (contactNormal.y != 0.0f) dynamicVelocity.Velocity.y = 0.0f;
}