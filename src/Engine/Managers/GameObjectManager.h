#pragma once
#include "../Core/GameObject.h"
#include "../Core/Events.h"

#include <unordered_map>

namespace Engine
{

    class GameObjectManager : public IEventDispatcher<GameObjectDeletedData>
    {
    public:
        ~GameObjectManager() = default;

        static GameObjectManager& Get();

        GameObject* CreateGameObject(GameObject::FilterTag tag, const char* name="Unknown");

        GameObject* GetGameObjectByID(GameObjectID ID);

        void DestroyGameObject(GameObjectID ID);
        void CleanupGameObjects();

    private:
        GameObjectManager() = default;

        GameObjectID m_nextGameObjectID = 0;

        std::unordered_map<GameObjectID, std::unique_ptr<GameObject>> m_gameObjects;
        std::queue< GameObject* > m_gameObjectsToCleanup;

    friend class Application;   // only Application can create a manager
    };
};


