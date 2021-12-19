#include "GameObject.h"
#include "Components/RigidbodyComponent.h"
#include "Components/ActorComponent.h"
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
        UpdateComponentIfExists<ActorComponent>(dt);
        UpdateComponentIfExists<RigidbodyComponent>(dt);
    }

    void GameObject::Render()
    {
        //for (auto renderableComponent : m_renderableComponents)
        //    renderableComponent.second->Render();
    }
};