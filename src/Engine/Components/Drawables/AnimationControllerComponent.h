#pragma once
#include "../Core/IComponent.h"
#include "SpriteDrawableComponent.h"

namespace Engine
{
	class AnimationClip;
	class AnimationControllerComponent : public IComponent
	{
	public:
		AnimationControllerComponent(GameObject& obj);
		~AnimationControllerComponent() = default;

		void OnCreate() override;
		void OnDestroy() override;

		void Update(float dt) override;
		void FixedUpdate(float dt) override;

		void AddAnimationClip(const char* name);
	private:
		// placeholder for now
		float m_currentTimer = 0.0f;
		size_t m_currentSample = 0;
		size_t m_maxSamples = 0;
		std::shared_ptr<AnimationClip> m_animationClip;
		SpriteDrawableComponent* m_spriteComponent = nullptr;
	};
}