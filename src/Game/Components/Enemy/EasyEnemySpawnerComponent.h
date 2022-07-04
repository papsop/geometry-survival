#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
namespace Game
{
	class EasyEnemySpawnerComponent : public Engine::IComponent
	{
	public:
		EasyEnemySpawnerComponent(Engine::GameObject& obj);
		~EasyEnemySpawnerComponent();

		void Update(float dt) override;

		void OnCreate() override;

	private:
		float m_cooldown = 1.0f;
		float m_currentCooldown;
	};
}