#include "GameObject.h"
#include "Components/Normal/RigidbodyComponent.h"
#include "Components/Normal/ActorComponent.h"
#include "Components/Normal/PlayerControllerComponent.h"
#include "Components/Normal/SeekingEnemyController.h"
#include <iostream>
namespace Game
{

    void GameObject::NotifyComponents()
    {
        for (auto component : m_components)
            component.second->OnGameObjectChanged();
    }

    void GameObject::Update(float dt)
    {
        // Order of component's updates
        UpdateComponentIfExists<SeekingEnemyController>(dt);
        UpdateComponentIfExists<PlayerControllerComponent>(dt);
        UpdateComponentIfExists<ActorComponent>(dt);
        UpdateComponentIfExists<RigidbodyComponent>(dt);
    }

    void GameObject::Render()
    {
        //for (auto renderableComponent : m_renderableComponents)
        //    renderableComponent.second->Render();
    }
};