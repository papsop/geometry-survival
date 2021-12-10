#pragma once
#include <math.h>
#include <SFML/System/Vector2.hpp>
#define _USE_MATH_DEFINES
#include<math.h>

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
            return { cos((Rotation - 90.0f) * 3.14159f / 180.0f), sin((Rotation - 90.0f) * 3.14159f / 180.0f) };
        }
    };
};