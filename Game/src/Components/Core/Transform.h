#pragma once
#include <math.h>
#include <SFML/System/Vector2.hpp>
#include "../../Utils/VectorUtils.h"

namespace Game
{
    struct Transform
    {
        sf::Vector2f Position;
        float Rotation;
        sf::Vector2f Scale;

        Transform() : Position(sf::Vector2f(0.0f, 0.0f)), Rotation(0.0f), Scale(sf::Vector2f(1.0f, 1.0f)) {}

        sf::Vector2f Forward()
        {
            return { cosf(math::DEG_TO_RAD(Rotation)), sinf(math::DEG_TO_RAD(Rotation)) };
        }
    };
};