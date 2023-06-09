#pragma once
#include "AnimatorController.h"
#include "../../Managers/AnimationData.h"

#include "../Core/IComponent.h"
#include "../../Core/Signal.h"

#include <memory>
namespace Engine
{
	class SpriteDrawableComponent;

	struct AnimationPlayRequest 
	{
		std::shared_ptr<AnimationClip> Clip;
		bool ShouldLoop;
		Signal<void> OnStarted;
		Signal<void> OnFinished;
	};

	class AnimatorComponent final : public IComponent
	{
	public:
		AnimatorComponent(GameObject& obj);
		~AnimatorComponent() = default;

		void OnCreate() override;
		void OnDestroy() override;

		void Update(float dt) override;


		void SetAnimatorController(std::unique_ptr<AnimatorController> controller);

		void PlayAnimation(AnimationPlayRequest request);

		Signal<std::string> OnAnimationEvent;
	private:
		SpriteDrawableComponent* m_spriteComponent = nullptr;
		std::unique_ptr<AnimatorController> m_animatorController;

	};
}