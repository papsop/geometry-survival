#pragma once
#include <SFML/Graphics.hpp>
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
        };

        struct Circle
        {
            float Radius;
            sf::Color FillColor;
            sf::Color OutlineColor = sf::Color(0, 0, 0, 0);
            float OutlineThickness = 0.0f;
            const Engine::Transform& Transform;

            Circle(const Engine::Transform& transform) : Transform(transform) {};
        };

        struct Text
        {
            std::string Value;
            sf::Color Color;
            unsigned int Size;
            const Engine::Transform& Transform;
            bool ShouldCenter = false;

            Text(const Engine::Transform& transform) : Transform(transform) {};
        };

        struct Line
        {
            sf::Vertex Points[2];
        };
    };
};