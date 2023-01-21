#pragma once
#include <SFML/Graphics.hpp>
#include <Engine/Utils/VectorUtils.h>
#include <Engine/Core/GameObject/GameObject.h>

namespace Game
{

	struct WallFactoryDef
	{
		sf::Color Color = sf::Color::Yellow;
		Engine::math::Vec2 Position;
		Engine::math::Vec2 Size;
		float RotationDeg;
	};

	struct EnemyFactoryDef
	{
		Engine::math::Vec2 Position;
		float MovementSpeed;
		Engine::GameObject* Player;
	};

	struct ExperienceGlobeDef
	{
		Engine::math::Vec2 Position;
	};

	struct PlayerObjectDef
	{
		bool IncludeInputControl;
	};

	struct BulletFactoryDef
	{
		Engine::math::Vec2 Position;
		float Rotation;

		float Damage;
		int		BulletHits;
		bool	Scatter;
	};
}