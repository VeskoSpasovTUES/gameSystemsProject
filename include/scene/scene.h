#pragma once

#include <vector>

#include "ecs/entities/player.h"
#include "ecs/entities/wall.h"

class Scene
{
public:
    Player Player;
    std::vector<Wall> Walls;
};