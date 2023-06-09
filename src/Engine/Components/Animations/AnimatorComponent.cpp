#include "AnimatorComponent.h"
#include "../../Managers/AnimationManager.h"
#include "../Drawables/SpriteDrawableComponent.h"

namespace Engine
{

	AnimatorComponent::AnimatorComponent(GameObject& obj)
		: IComponent(obj)
	{
		SetRequiredComponents<SpriteDrawableComponent>();
	}

	void AnimatorComponent::OnCreate()
	{
		AnimationManager::Get().RegisterAnimator(this);
		m_spriteComponent = Owner.GetComponent<SpriteDrawableComponent>();
	}

	void AnimatorComponent::OnDestroy()
	{
		AnimationManager::Get().UnregisterAnimator(this);
	}

	void AnimatorComponent::Update(float dt)
	{

	}

	void AnimatorComponent::SetAnimatorController(std::unique_ptr<AnimatorController> controller)
	{
		m_animatorController = std::move(controller);
	}

}