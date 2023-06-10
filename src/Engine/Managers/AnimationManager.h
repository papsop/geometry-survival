#pragma once
#include "IManager.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

namespace Engine
{
	class AnimationControllerComponent;
	class AnimatorComponent;

	class AnimationManager : public IManager
	{
	public:

		static AnimationManager& Get();
		~AnimationManager() = default;


		void Update(float dt) override;
		void FixedUpdate(float dt) override;

		void RegisterAnimationController(AnimationControllerComponent* component);
		void UnregisterAnimationController(AnimationControllerComponent* component);

		void RegisterAnimator(AnimatorComponent* component);
		void UnregisterAnimator(AnimatorComponent* component);

		void SetAnimationsEnabled(bool val) { m_enabled = val; };
	protected:
		void VirtualOnInit() override;
		void VirtualOnDestroy() override;

	private:
		bool m_enabled = false;
		std::vector<AnimationControllerComponent*> m_animationControllers;
		std::vector<AnimatorComponent*> m_animatorComponents;

		AnimationManager() = default;

		friend class Application;
	};

};