#include "EntityManager.h"

#include "../Application.h"

// TODO: Entity cleanup and notifications about deletion

namespace Engine
{
    EntityManager& EntityManager::Get() { return Application::Instance().GetEntityManager(); }

    GameObject* EntityManager::CreateEntity(const char *name)
    {
        uint32_t ID = m_nextEntityID++;
        m_entities[ID] = std::make_unique<GameObject>(ID, name);
        return m_entities[ID].get();
    };

    GameObject* EntityManager::GetEntityByID(uint32_t ID)
    {
        return m_entities[ID].get();
    }

};