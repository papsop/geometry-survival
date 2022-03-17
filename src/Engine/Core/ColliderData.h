#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

struct CircleColliderData
{
    CircleColliderData(float radius, sf::Vector2f pos) : Radius(radius), Position(pos) {};
    float Radius;
    sf::Vector2f Position;

    sf::Rect<float> GetBoundingBox()
    {
        return { {Position.x - Radius, Position.y - Radius},  {Radius * 2, Radius * 2} };
    }

};

struct ColliderData
{
    std::vector<CircleColliderData> CircleColliders;
};