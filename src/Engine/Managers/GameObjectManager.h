#pragma once
#include "IManager.h"
#include "../Core/GameObject.h"
#include "../Core/Events.h"


#include <unordered_map>

namespace Engine
{

    class GameObjectManager : public IManager, public IEventDispatcher<E_GameObjectDeleted>
    {
    public:
        ~GameObjectManager() = default;

        static GameObjectManager& Get();

        GameObject* CreateGameObject(const char* name="Unknown");
        GameObject* GetGameObjectByID(GameObjectID ID);

        void DestroyGameObject(GameObjectID ID);
        void CleanupGameObjects();
    protected:
        void OnDestroy() override;
    private:
        GameObjectManager() = default;

        GameObjectID m_nextGameObjectID = 0;

        std::unordered_map<GameObjectID, std::unique_ptr<GameObject>> m_gameObjects;
        std::queue< GameObject* > m_gameObjectsToCleanup;

    friend class Application;   // only Application can create a manager
    };
};