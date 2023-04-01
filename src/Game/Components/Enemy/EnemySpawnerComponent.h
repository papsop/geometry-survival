#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>

namespace Game
{
	class EnemySpawnerComponent : public Engine::IComponent
	{
	public:
		EnemySpawnerComponent(Engine::GameObject& obj);
		~EnemySpawnerComponent() = default;

		void OnDestroy() override;
	protected:
		void VirtualOnActivated() override;
		void VirtualOnDeactivated() override;

	private:
		float m_currentCooldown;
	};
}