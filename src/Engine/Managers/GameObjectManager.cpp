#include "GameObjectManager.h"

#include "../Application.h"
#include "../Core/EventData.h"

// TODO: Entity cleanup and notifications about deletion

namespace Engine
{
    GameObjectManager& GameObjectManager::Get() { return Application::Instance().GetGameObjectManager(); }

	void GameObjectManager::VirtualOnDestroy()
	{
        m_gameObjects.clear();
	}

    GameObject* GameObjectManager::CreateGameObject(const char *name, GameObjectTag tag)
    {
        uint32_t ID = m_nextGameObjectID++;
        m_gameObjects[ID] = std::make_unique<GameObject>(ID, name, tag);
        return m_gameObjects[ID].get();
    };

    GameObject* GameObjectManager::GetGameObjectByID(uint32_t ID)
    {
        if (m_gameObjects.find(ID) != m_gameObjects.end())
            return m_gameObjects[ID].get();
        else
        {
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

            event::E_GameObjectDeleted eventData(e->ID);

            m_gameObjects.erase(e->ID);
            m_gameObjectsToCleanup.pop();
            
            EventManager::Get().DispatchEvent(eventData);
        }
    }
};