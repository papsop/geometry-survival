#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include "../Player/LevelComponent.h"

namespace Game
{
	class ExperienceBarComponent : public Engine::IComponent
	{
	public:
		ExperienceBarComponent(Engine::GameObject& obj);
		~ExperienceBarComponent() override;

		void Update(float dt) override;

		void OnCreate() override;

	private:
		LevelComponent* m_playerLevelComponent		= nullptr;
		Engine::RectTransform* m_parentTransform	= nullptr;
		Engine::RectTransform* m_ownerTransform		= nullptr;
	};
}