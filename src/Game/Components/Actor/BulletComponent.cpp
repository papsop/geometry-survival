#include "BulletComponent.h"
#include "ActorComponent.h"

#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/ComponentManager.h>

namespace Game
{

    BulletComponent::BulletComponent(Engine::GameObject& obj, float damage)
        : IComponent(obj)
        , m_damage(damage)
    {
    }

    void BulletComponent::OnCreate()
    {
        Engine::ComponentManager::Get().RegisterComponent(this);
    }

    BulletComponent::~BulletComponent()
    {
        Engine::ComponentManager::Get().UnregisterComponent(this);
    }

    void BulletComponent::Update(float dt)
    {
        m_timeToDie -= dt;
        if (m_timeToDie <= 0.0f)
            Owner.Destroy();
    }

	void BulletComponent::OnCollisionStart(Engine::CollisionData& collision)
	{
        auto otherActor = collision.Other->GetComponent<ActorComponent>();
        if (otherActor != nullptr)
            otherActor->AddCommand<DamageCommand>(m_damage);

        Owner.Destroy();
	}

}