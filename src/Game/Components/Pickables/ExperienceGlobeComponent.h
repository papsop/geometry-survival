#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/PhysicsManager.h>

namespace Game
{
	class ExperienceGlobeComponent : public Engine::IComponent
	{
	public:
		ExperienceGlobeComponent(Engine::GameObject& obj);
		~ExperienceGlobeComponent() override;
		void OnCreate() override;

		void OnCollisionStart(Engine::CollisionData& other) override;
		void Update(float dt) override;

	private:
		Engine::GameObject* m_markedBy;
	};
};