#include "rectanglecollisionsystem.h"
#include <raymath.h>
#include <cmath>
#include <algorithm>

bool RectangleCollisionSystem::RayVsRectangle(const Vector2& rayOrigin, const Vector2& rayDirection, const TransformComponent& targetTransform, const RectangleColliderComponent& targetCollider, Vector2& contactPoint, Vector2& contactNormal, float& hitTimeNear)
{
	contactPoint = { 0,0 };
	contactNormal = { 0,0 };

	Vector2 direction = rayDirection;

	Vector2 nearVector = Vector2Divide(Vector2Subtract(targetTransform.Position, rayOrigin), direction);
	Vector2 farVector = Vector2Divide(Vector2Subtract(Vector2Add(targetTransform.Position, targetCollider.Size), rayOrigin), direction);

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