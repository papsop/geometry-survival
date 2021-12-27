#include "GameObject.h"
#include "../Debug/Logger.h"
#include <iostream>

namespace Game
{
   GameObject::GameObject(uint32_t id, const char* debugName) 
        : ID(id)
        , DebugName(debugName)
        , m_transform() 
    {
       LOG_INFO("Creating GameObject [ID: %d, Name: '%s']", id, debugName);
    };

    void GameObject::NotifyComponents()
    {
        for (auto component : m_components)
            component.second->OnGameObjectChanged();
    }

    void GameObject::Update(float dt)
    {
        // Order of component's updates
        UpdateComponentIfExists<InputComponent>(dt);
        UpdateComponentIfExists<ActorComponent>(dt);
        UpdateComponentIfExists<RigidbodyComponent>(dt);
    }

    void GameObject::Render()
    {
        //for (auto renderableComponent : m_renderableComponents)
        //    renderableComponent.second->Render();
    }
};