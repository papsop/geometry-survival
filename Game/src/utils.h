#pragma once
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <stdint.h>
#include "Components/Transform.h"

namespace Game
{
    namespace view
    {
        struct Shape 
        {
            size_t PointCount;
            float Radius;
            sf::Color Color;
            sf::Vector2f Position;
            float Rotation;
            sf::Vector2f Scale;

            void ImportTransform(const Transform& transform)
            {
                Position = transform.Position;
                Rotation = transform.Rotation;
                Scale = transform.Scale;
            }

            operator sf::CircleShape() const
            {
                auto obj = sf::CircleShape();
                obj.setPointCount(this->PointCount);
                obj.setRadius(this->Radius);
                obj.setFillColor(this->Color);
                obj.setPosition(this->Position);
                obj.setRotation(this->Rotation);
                obj.setScale(this->Scale);
                return obj;
            }
        };
    };
};