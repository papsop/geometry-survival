#include "LevelComponent.h"
#include <Engine/Managers/ComponentManager.h>
#include <Engine/Managers/PhysicsManager.h>
#include <Engine/Managers/EventManager.h>
#include "../../Core/EventData.h"
#include "../../Physics/Filters.h"
#include "../../Managers/GameManager.h"

namespace Game
{

	LevelComponent::LevelComponent(Engine::GameObject& obj)
		: IComponent(obj)
	{
		m_firstLevelExperience = GameManager::Get()->GetFirstLevelExperience();
	}

	void LevelComponent::OnCreate()
	{
		Engine::ComponentManager::Get().RegisterComponent(this);
	}

	LevelComponent::~LevelComponent()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
	}

	void LevelComponent::ApplyExperience(float amount)
	{
		m_totalExp += amount;
		float nextLevelExp = GetNextLevelExperience();
		if (m_totalExp >= nextLevelExp)
		{
			//GameManager::Get()->SetGameState(GameManager::GameState::Paused);
			Engine::EventManager::Get().DispatchEvent(event::E_PlayerLeveledUp());
			m_currentLevel++;
			m_totalExp -= nextLevelExp;
			LOG_WARN("Leveled up, current level '%d', next level experience '%f'", m_currentLevel, GetNextLevelExperience());
		}
	}

	float LevelComponent::GetCurrentLevelProgress()
	{
		return m_totalExp / GetNextLevelExperience();
	}

	float LevelComponent::GetNextLevelExperience()
	{
		return m_firstLevelExperience * std::pow(2, m_currentLevel);
	}

	void LevelComponent::Update(float dt)
	{
		
	}

	void LevelComponent::Debug(Engine::view::IViewStrategy* viewStrategy)
	{
		Engine::math::Vec2 pos = Owner.GetTransform()->GetPosition() + Engine::math::Vec2(0.0f, 6.0f);
		std::string expCount = "LevelProgress " + std::to_string(GetCurrentLevelProgress());
		viewStrategy->DebugRenderText(Engine::ITransform::PositionSpace::WorldSpace, expCount, pos, 12.0f, sf::Color::Yellow);
	}
}