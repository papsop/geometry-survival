#include "AnimationManager.h"
#include "../Application.h"

namespace Engine
{
	AnimationManager& AnimationManager::Get()
	{
		return Application::Instance().GetAnimationManager();
	}

	void AnimationManager::VirtualOnInit()
	{
	}

	void AnimationManager::VirtualOnDestroy()
	{
	}

	void AnimationManager::Update(float dt)
	{
		if (!m_enabled)
			return;

		for (auto& controller : m_animationControllers)
		{
			controller->Update(dt);
		}
	}

	void AnimationManager::FixedUpdate(float dt)
	{
		if (!m_enabled)
			return;

		for (auto& controller : m_animationControllers)
		{
			controller->FixedUpdate(dt);
		}
	}

	void AnimationManager::RegisterAnimationController(AnimationControllerComponent* component)
	{
		m_animationControllers.push_back(component);
	}

	void AnimationManager::UnregisterAnimationController(AnimationControllerComponent* component)
	{
		m_animationControllers.erase(std::remove(m_animationControllers.begin(), m_animationControllers.end(), component), m_animationControllers.end());
	}

}