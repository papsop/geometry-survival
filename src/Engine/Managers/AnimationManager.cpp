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

	}

	void AnimationManager::FixedUpdate(float dt)
	{

	}


}