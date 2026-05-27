#include "MovementSystem.h"

void MovementSystem::Update(TransformComponent& transform, VelocityComponent& velocity, float dt)
{
    transform.Position.x += velocity.Velocity.x * dt;
    transform.Position.y += velocity.Velocity.y * dt;

    if (transform.Position.x < 0)
    {
        transform.Position.x = 0;
    }

    if (transform.Position.x > 1230)
    {
        transform.Position.x = 1230;
    }

    if (transform.Position.y < 0)
    {
        transform.Position.y = 0;
    }

    if (transform.Position.y > 670)
    {
        transform.Position.y = 670;
    }
}