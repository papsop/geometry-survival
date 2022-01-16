#include "EntityManager.h"

#include "../Application.h"

namespace Engine
{
    EntityManager& EntityManager::Get() { return Application::Instance().GetEntityManager(); }

    std::weak_ptr<GameObject> EntityManager::CreateEntityReturnEntity(const char *name)
    {
        uint32_t ID = m_nextEntityID++;
        std::shared_ptr<GameObject> newGameObject = std::make_shared<GameObject>(ID, name);
        m_entities[ID] = newGameObject;
        return newGameObject;
    };
    
    uint32_t EntityManager::CreateEntityReturnID(const char* name)
    {
        if (auto entity = CreateEntityReturnEntity(name).lock())
            return entity->ID;
    };

    std::weak_ptr<GameObject> EntityManager::GetEntityByID(uint32_t ID)
    {
        return m_entities[ID];
    }

};