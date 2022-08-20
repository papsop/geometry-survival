#pragma once
#include <SFML/Graphics.hpp>
#include "../Components/Core/Transform.h"

namespace Engine
{
    namespace view
    {
        struct Line
        {
            sf::Vertex Points[2];
        };
       
		struct Renderable
		{

			struct Shape
			{
				size_t PointCount;
				float Radius;
				sf::Color Color;
			};

			struct Circle
			{
				float Radius;
				sf::Color FillColor;
				sf::Color OutlineColor;
				float OutlineThickness;
			};

			struct Rectangle
			{
				math::Vec2 Size;
				sf::Color FillColor;
			};

			struct Text
			{
				std::string Value;
				sf::Color Color;
				unsigned int Size;
				bool ShouldCenter;
			};

			enum class RenderableType
			{
				SHAPE,
                CIRCLE,
                RECTANGLE,
                TEXT
			};

            // ===============================================
            // Renderable members
            // ===============================================

            RenderableType Type;
			ITransform::AbsoluteTransform Transform;
			union
			{
				Shape shape;
				Circle circle;
				Rectangle rectangle;
			};

            Renderable(RenderableType type) : Type(type) {};
		};
    };
};