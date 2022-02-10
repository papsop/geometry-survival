#include "GameObjectManager.h"

#include "../Application.h"
#include "../Core/EventData.h"

// TODO: Entity cleanup and notifications about deletion

namespace Engine
{
    GameObjectManager& GameObjectManager::Get() { return Application::Instance().GetGameObjectManager(); }

    GameObject* GameObjectManager::CreateGameObject(const char *name)
    {
        uint32_t ID = m_nextGameObjectID++;
        m_gameObjects[ID] = std::make_unique<GameObject>(ID, name);
        return m_gameObjects[ID].get();
    };

    GameObject* GameObjectManager::GetGameObjectByID(uint32_t ID)
    {
        if (m_gameObjects.find(ID) != m_gameObjects.end())
            return m_gameObjects[ID].get();
        else
        {
            LOG_WARN("Trying to retrieve non-existent EntityID '%d'", ID);
            return nullptr;
        }
            
    }

    void GameObjectManager::DestroyGameObject(uint32_t ID)
    {
        auto gameObject = GetGameObjectByID(ID);
        if (gameObject != nullptr)
        {
            gameObject->m_shouldDestroy = true;
            m_gameObjectsToCleanup.push(gameObject);
        }
    }

    void GameObjectManager::CleanupGameObjects()
    {
        while (!m_gameObjectsToCleanup.empty())
        {
            auto e = m_gameObjectsToCleanup.front();

            GameObjectDeletedData eventData(e->ID);

            LOG_INFO("DELETED %d", e->ID);
            m_gameObjects.erase(e->ID);
            m_gameObjectsToCleanup.pop();
            
            
            EventManager::Get().DispatchEvent<GameObjectDeletedData>(eventData);
        }
    }

};