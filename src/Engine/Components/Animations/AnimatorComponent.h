#pragma once
#include "../Core/IComponent.h"
#include "../../Managers/ResourceManager.h"
#include "../../Managers/AnimationManager.h"
#include "IAnimationPlayRequester.h"
#include "AnimationData.h"
#include "AnimatorController.h"

#include "../Drawables/SpriteDrawableComponent.h"
#include "../../Core/Signal.h"

#include <memory>
namespace Engine
{

	class AnimatorComponent final : public IComponent
	{
	public:
		AnimatorComponent(GameObject& obj);
		~AnimatorComponent() = default;

		void VirtualOnCreate() override;
		void OnDestroy() override;

		void Update(float dt) override;

		void SetAnimatorController(std::unique_ptr<AnimatorController> controller);

		void RequestAnimationPlay(AnimationPlayRequest request);

		Signal<std::string> OnAnimationEvent;

	private:
		void ApplySampleDataToSprite(AnimationSample& sample);

		SpriteDrawableComponent* m_spriteComponent = nullptr;
		std::unique_ptr<AnimatorController> m_animatorController;

		AnimationPlayRequest m_currentRequest;
		AnimationClip* m_currentClip = nullptr;

		size_t m_currentSampleIndex = 0;
		float m_currentSampleTimer = 0.0f;
		bool m_requestFinished = false;
		bool m_shouldNotify = false;
	};
}