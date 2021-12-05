#pragma once
#include <math.h>
#include <SFML/System/Vector2.hpp>

sf::Vector2f normalize(sf::Vector2f vec)
{
    float length = sqrt(pow(vec.x,2) + pow(vec.y,2));
    if (length == 0)
        return { vec };
    else
        return { vec / length };
}

float dotProduct(sf::Vector2f a, sf::Vector2f b)
{
    // expects normalized :shrug:
    return a.x * b.x + a.y * b.y;
}