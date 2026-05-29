#include "core/input.h"

#include <raylib.h>

bool Input::IsKeyPressed(int key)
{
    return ::IsKeyPressed(key);
}

bool Input::IsKeyDown(int key)
{
    return ::IsKeyDown(key);
}

bool Input::IsMouseButtonPressed(int button)
{
    return ::IsMouseButtonPressed(button);
}