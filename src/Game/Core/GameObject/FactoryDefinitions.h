#pragma once
#include <SFML/Graphics.hpp>
#include <Engine/Utils/VectorUtils.h>

namespace Game
{
	struct WallFactoryDef
	{
		sf::Color Color = sf::Color::Yellow;
		Engine::math::Vec2 Position;
		Engine::math::Vec2 Size;
		float RotationDeg;
	};
}