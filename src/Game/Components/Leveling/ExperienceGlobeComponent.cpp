#include "ExperienceGlobeComponent.h"
#include <Engine/Components/Physics.h>

namespace Game
{
	ExperienceGlobeComponent::ExperienceGlobeComponent(Engine::GameObject& obj)
		: IComponent(obj)
	{
		SetRequiredComponents<Engine::CircleFixtureComponent>();
	}

	ExperienceGlobeComponent::~ExperienceGlobeComponent()
	{

	}

};