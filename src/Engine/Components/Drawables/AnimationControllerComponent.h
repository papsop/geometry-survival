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
	private:
		SpriteDrawableComponent* m_spriteComponent = nullptr;
		std::vector<std::unique_ptr<AnimationState>> m_animationStates;
		AnimationState* m_currentAnimationState = nullptr;
		AnimationClip* m_currentAnimationClip = nullptr;
		float m_currentSampleTimer = 0.0f;
		size_t m_currentSample = 0;

		void ApplySampleData(const AnimationSample& sample);
		void SwapAnimationState(AnimationState* newState);
	};
}