#pragma once
#include "../Core/IComponent.h"
#include "SpriteDrawableComponent.h"
#include "AnimationStateMachine.h"

#include <functional>
namespace Engine
{
	class AnimationClip;
	class AnimationSample;

	class AnimationControllerComponent : public IComponent
	{
	public:
		friend class AnimationStateMachine;

		AnimationControllerComponent(GameObject& obj);
		~AnimationControllerComponent() = default;

		void OnCreate() override;
		void OnDestroy() override;

		void Update(float dt) override;
		void FixedUpdate(float dt) override;

		// Stops updating stateMachine while this clip is running
		void PlayForcedAnimationClip(const char* animationClipName);
		std::string GetRunningAnimationClipName();

		// TODO: Add one-shot state that calls a lambda when it finishes
		// So it's possible to play death animation and react when it ends
		AnimationStateMachine StateMachine;
	private:
		SpriteDrawableComponent* m_spriteComponent = nullptr;
		AnimationClip* m_currentAnimationClip = nullptr;
		float m_currentSampleTimer = 0.0f;
		size_t m_currentSample = 0;
		bool m_isPlayingForcedAnimation = false;

		void PlayAnimationClipFromSM(const char* animationClipName);
    void ApplySampleData(const AnimationSample& sample);
		void UpdateAnimation(float dt);
	};

}