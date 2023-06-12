#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace Engine
{
	class IAnimationPlayRequester
	{
	public:
		virtual void OnAnimationStarted() {};
		virtual void OnAnimationFinished() {};
	};

	struct AnimationSample
	{
		float Duration = 0.0f;							// normalized, so all the samples should sum up to 1.0f
		sf::Vector2i TextureCoord = { 0, 0 }; // top left corner of the sample
	};

	struct AnimationClip
	{
		std::string Name = "";
		sf::Vector2i SampleTextureSize = { 0, 0 }; // size of one sample in pixels
		std::string TextureName = "";
		bool Loopable = false;
		// duration of the whole animation
		std::vector<AnimationSample> Samples = {};

		bool operator==(const AnimationClip& rhs)
		{
			return (this->Name == rhs.Name && this->TextureName == rhs.TextureName);
		}
	};

	struct AnimationPlayData
	{
		const char* Clip;
		bool IsLooped;
		// maybe more later
	};

	struct AnimationPlayRequest
	{
		AnimationPlayData Data;
		IAnimationPlayRequester* Requester = nullptr; // nullptr => anonymous request, no notifications
	};
}