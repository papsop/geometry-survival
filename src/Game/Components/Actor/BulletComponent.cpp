#include "BulletComponent.h"

#include <Engine/Core/GameObject.h>
#include <Engine/Managers/SubsystemManager.h>

namespace Game
{

    BulletComponent::BulletComponent(Engine::GameObject& obj)
        : IComponent(obj)
    {
    }

    void BulletComponent::OnCreate()
    {
        Engine::SubsystemManager::Get().RegisterComponent(this);
    }

    BulletComponent::~BulletComponent()
    {
        Engine::SubsystemManager::Get().UnregisterComponent(this);
    }

    void BulletComponent::Update(float dt)
    {
        m_timeToDie -= dt;
        if (m_timeToDie <= 0.0f)
            Owner.Destroy();
    }

	void BulletComponent::OnCollisionStart(Engine::GameObject* other)
	{
        Owner.Destroy();
	}

}