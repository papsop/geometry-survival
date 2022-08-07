#include "LevelComponent.h"
#include <Engine/Managers/ComponentManager.h>
#include <Engine/Managers/PhysicsManager.h>
#include "../../Physics/Filters.h"

namespace Game
{

	LevelComponent::LevelComponent(Engine::GameObject& obj)
		: IComponent(obj)
	{
		
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
	}

	void LevelComponent::Update(float dt)
	{
		
	}

	void LevelComponent::Debug(Engine::view::IViewStrategy* viewStrategy)
	{
		Engine::math::Vec2 pos = Owner.GetTransform().Position + Engine::math::Vec2(0.0f, 6.0f);
		std::string expCount = "Exp " + std::to_string(m_totalExp);
		viewStrategy->DebugRenderText(expCount, pos, 12.0f, sf::Color::Yellow);
	}
}