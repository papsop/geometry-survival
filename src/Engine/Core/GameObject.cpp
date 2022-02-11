#include "GameObject.h"
#include "../Debug/Logger.h"
#include "../Managers/GameObjectManager.h"
#include <iostream>

namespace Engine
{
   GameObject::GameObject(uint32_t id, const char* debugName) 
        : ID(id)
        , DebugName(debugName)
        , m_transform() 
    {
       LOG_DEBUG("Creating GameObject [ID: %d, Name: '%s']", id, debugName);
    };

    void GameObject::NotifyComponents()
    {
        for (auto&& component : m_components)
            component.second->OnGameObjectChanged();
    }

    void GameObject::Destroy()
    {
        Engine::GameObjectManager::Get().DestroyGameObject(ID);
    }
};