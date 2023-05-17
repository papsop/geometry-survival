#pragma once
#include "../Core/IComponent.h"
#include "SpriteDrawableComponent.h"
#include "AnimationStateMachine.h"

namespace Engine
{
	class AnimationClip;
	class AnimationSample;

	class AnimationControllerComponent : public IComponent
	{
	public:
		AnimationControllerComponent(GameObject& obj);
		~AnimationControllerComponent() = default;

		void OnCreate() override;
		void OnDestroy() override;

		void Update(float dt) override;
		void FixedUpdate(float dt) override;

		AnimationState* AddAnimationState(const char* animationClipName);

    template<typename T>
    void AddAnyStateTransition(AnimationState* target, const T& variable, TransitionConditionType conditionType, T value);
	private:
		SpriteDrawableComponent* m_spriteComponent = nullptr;
		std::vector<std::unique_ptr<AnimationState>> m_animationStates;
		AnimationState* m_currentAnimationState = nullptr;
		AnimationClip* m_currentAnimationClip = nullptr;
		float m_currentSampleTimer = 0.0f;
		size_t m_currentSample = 0;
		std::vector<std::unique_ptr<IAnimationStateTransition>> m_anyStateTransitions;

    void ApplySampleData(const AnimationSample& sample);
    void SwapAnimationState(AnimationState* newState);

		void UpdateAnimation(float dt);
		void CheckStateTransitions();
	};
	// TODO: .inl file, but too lazy rn
  template<typename T>
  void Engine::AnimationControllerComponent::AddAnyStateTransition(AnimationState* target, const T& variable, TransitionConditionType conditionType, T value)
  {
    AnimationStateTransition<T>* trans_ptr = new AnimationStateTransition<T>(target, variable, conditionType, value);
    auto transition = std::unique_ptr<IAnimationStateTransition>(trans_ptr);
    m_anyStateTransitions.push_back(std::move(transition));
  }

}