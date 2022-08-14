#pragma once
#include <Engine/Debug/IDebuggable.h>
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>

namespace Game
{
	class LevelComponent : public Engine::IComponent, Engine::IDebuggableComponent
	{
	public:
		LevelComponent(Engine::GameObject& obj);
		~LevelComponent() override;

		void OnCreate() override;
		void Update(float dt) override;

		void Debug(Engine::view::IViewStrategy* viewStrategy) override;
		void ApplyExperience(float amount);

		int   GetCurrentLevel() { return m_currentLevel; }
		float GetNextLevelExperience();
		float GetCurrentLevelProgress();
	private:
		float m_totalExp = 0;
		int m_currentLevel = 0;
		float m_firstLevelExperience;
	};
}