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
		float MaxHealth;
		float DamagePerSecond;
		sf::Color Color;
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

		// burning effect 
		float BurningDamage = 0.0f; // per second
	};

	struct CombatTextDef
	{
		Engine::math::Vec2 Position;
		int Damage;
	};
}