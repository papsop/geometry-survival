#pragma once
#include "IManager.h"
#include "../Components/Drawables/AnimationControllerComponent.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

namespace Engine
{

	struct AnimationSample
	{
		float Duration = 0.0f;							// normalized, so all the samples should sum up to 1.0f
		sf::Vector2i TextureCoord = {0, 0}; // top left corner of the sample
	};

	struct AnimationClip
	{
		std::string Name = "";
		sf::Vector2i SampleTextureSize = {0, 0}; // size of one sample in pixels
		std::string TextureName = "";
		bool Loopable = false;
		// duration of the whole animation
		std::vector<AnimationSample> Samples = {};
	};

	class AnimationManager : public IManager
	{
	public:

		static AnimationManager& Get();
		~AnimationManager() = default;


		void Update(float dt) override;
		void FixedUpdate(float dt) override;

		void RegisterAnimationController(AnimationControllerComponent* component);
		void UnregisterAnimationController(AnimationControllerComponent* component);

		void SetAnimationsEnabled(bool val) { m_enabled = val; };
	protected:
		void VirtualOnInit() override;
		void VirtualOnDestroy() override;

	private:
		bool m_enabled = false;
		std::vector<AnimationControllerComponent*> m_animationControllers;

		AnimationManager() = default;

		friend class Application;
	};

};