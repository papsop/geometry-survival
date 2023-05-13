#pragma once
#include "IManager.h"
#include <SFML/Graphics.hpp>

namespace Engine
{

	struct AnimationSample
	{
		float Duration;
		sf::Vector2i TextureCoord; // top left corner of the sample
	};

	struct AnimationClip
	{
		sf::Vector2i SampleTextureSize; // size of one sample in pixels
		std::vector<AnimationClip> Samples;
	};

	class AnimationManager : public IManager
	{
	public:

		static AnimationManager& Get();
		~AnimationManager() = default;


		void Update(float dt) override;
		void FixedUpdate(float dt) override;

		void SetAnimationsEnabled(bool val) { m_enabled = val; };
	protected:
		void VirtualOnInit() override;
		void VirtualOnDestroy() override;

	private:
		bool m_enabled = false;

		AnimationManager() = default;

		friend class Application;
	};

};