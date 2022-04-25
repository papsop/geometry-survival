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
            Engine::Transform* Transform;

            Shape(Engine::Transform* transform) : Transform(transform) {};
        };

        struct Circle
        {
            float Radius;
            sf::Color FillColor;
            sf::Color OutlineColor = sf::Color(0, 0, 0, 0);
            float OutlineThickness = 0.0f;
            Engine::Transform* Transform;

            Circle(Engine::Transform* transform) : Transform(transform) {};
        };

        struct Rectangle
        {
            math::Vec2 Size;
            sf::Color FillColor;
            Engine::Transform* Transform;

            Rectangle(Engine::Transform* transform) : Transform(transform) {};
        };

        struct Text
        {
            std::string Value;
            sf::Color Color;
            unsigned int Size;
            Engine::Transform* Transform;
            bool ShouldCenter = false;

            Text(Engine::Transform* transform) : Transform(transform) {};
        };

        struct Line
        {
            sf::Vertex Points[2];
        };
        
        enum class RENDERABLE_TYPE
		{
			SHAPE, CIRCLE, RECTANGLE
		};
		struct Renderable
		{
            RENDERABLE_TYPE type;
			union
			{
				Shape shape;
				Circle circle;
				Rectangle rectangle;
			};

            Renderable(RENDERABLE_TYPE type) : type(type) {};
		};
    };
};