#pragma once
#include "IManager.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

namespace Engine
{

	struct AnimationSample
	{
		float Duration = 0.0f;
		sf::Vector2i TextureCoord = {0, 0}; // top left corner of the sample
	};

	struct AnimationClip
	{
		std::string Name = "";
		sf::Vector2i SampleTextureSize = {0, 0}; // size of one sample in pixels
		std::shared_ptr<sf::Texture> Texture = nullptr;
		bool Loopable = false;
		// duration
		std::vector<AnimationSample> Samples = {};
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