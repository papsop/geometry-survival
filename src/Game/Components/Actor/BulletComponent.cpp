#include "BulletComponent.h"

#include <Engine/Core/GameObject.h>
#include <Engine/Components/Physics/RigidbodyComponent.h>

namespace Game
{

    BulletComponent::BulletComponent(Engine::GameObject& obj)
        : IComponent(obj)
    {
        Requires<Engine::RigidbodyComponent>();
    }

    void BulletComponent::Update(float dt)
    {}
}