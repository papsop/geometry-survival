#include "GameObject.h"
#include "../Debug/Logger.h"
#include "../Managers/GameObjectManager.h"
#include <iostream>

namespace Engine
{
   GameObject::GameObject(uint32_t id, FilterTag tag, const char* debugName) 
        : c_ID(id)
        , c_DebugName(debugName)
        , c_Tag(tag)
        , m_transform() 
    {
       LOG_DEBUG("Creating GameObject [ID: %d, Name: '%s']", id, debugName);
    };

    void GameObject::OnCollision(GameObject& other)
    {
        for (auto& c : m_components)
            c.second->OnCollision(other);
    }

    void GameObject::Destroy()
    {
        Engine::GameObjectManager::Get().DestroyGameObject(c_ID);
    }
};