#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>

struct CircleColliderData
{
    CircleColliderData(float radius, sf::Vector2f pos) : Radius(radius), Position(pos) {};
    float Radius;
    sf::Vector2f Position;
};

struct ColliderData
{
    std::vector<CircleColliderData> CircleColliders;
};