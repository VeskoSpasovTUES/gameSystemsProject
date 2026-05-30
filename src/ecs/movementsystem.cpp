#include "ecs/systems/MovementSystem.h"

void MovementSystem::Update(TransformComponent& transform, VelocityComponent& velocity, float dt)
{
    transform.Position.x += velocity.Velocity.x * dt;
    transform.Position.y += velocity.Velocity.y * dt;
}