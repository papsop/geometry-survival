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

    void EntityManager::DestroyEntity(uint32_t ID)
    {
        auto entity = GetEntityByID(ID);
        entity->m_shouldDestroy = true;
        m_entitiesToCleanup.push(entity);
    }

    void EntityManager::CleanupEntities()
    {
        while (!m_entitiesToCleanup.empty())
        {
            auto e = m_entitiesToCleanup.front();
            LOG_INFO("DELETED %d", e->ID);
            m_entities.erase(e->ID);
            m_entitiesToCleanup.pop();
            
            // @TODO: NOTIFICATION ABOUT DELETION
        }
    }

};