#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>

namespace Game
{
	class ExperienceGlobeComponent : public Engine::IComponent
	{
	public:
		ExperienceGlobeComponent(Engine::GameObject& obj);
		~ExperienceGlobeComponent() override;

	};
};