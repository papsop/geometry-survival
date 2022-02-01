#pragma once
#include <SFML/Graphics.hpp>
#include <stdint.h>
#include "../Components/Core/Transform.h"

namespace Engine
{
    namespace view
    {
        struct Shape
        {
            size_t PointCount;
            float Radius;
            sf::Color Color;
            const Engine::Transform& Transform;

            Shape(const Engine::Transform& transform) : Transform(transform) {};

            operator sf::CircleShape() const
            {
                auto obj = sf::CircleShape();
                obj.setPointCount(PointCount);
                obj.setRadius(Radius);
                obj.setFillColor(Color);
                obj.setPosition(Transform.Position);
                // SFML uses bearings, north is 0 and east is 90 (the fuck?)
                float angle = 360.0f - (Transform.Rotation - 90.0f);
                obj.setRotation(angle);
                obj.setScale(Transform.Scale);
                obj.setOrigin(Radius, Radius);
                return obj;
            }
        };

        struct Text
        {
            std::string Value;
            sf::Color Color;
            unsigned int Size;
            const Engine::Transform& Transform;
            bool ShouldCenter = false;

            Text(const Engine::Transform& transform) : Transform(transform) {};

            operator sf::Text() const
            {
                auto obj = sf::Text();
                obj.setString(Value);
                obj.setCharacterSize(Size);
                obj.setFillColor(Color);
                obj.setRotation(Transform.Rotation);
                obj.setScale(Transform.Scale);
                obj.setPosition(Transform.Position);
                return obj;
            }
        };

        struct Line
        {
            sf::Vertex Points[2];
        };
    };
};