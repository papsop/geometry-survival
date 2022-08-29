#pragma once
#include "IManager.h"
#include "../Core/GameObject/GameObject.h"
#include "../Core/Events.h"


#include <unordered_map>

namespace Engine
{

    class GameObjectManager : public IManager
    {
    public:
        ~GameObjectManager() = default;

        static GameObjectManager& Get();

        GameObject* CreateGameObject(const char* name, GameObjectTag tag, const ITransform::TransformDefinition& transformDef);
        GameObject* GetGameObjectByID(GameObjectID ID);

        void Update(float dt) override;
        void DestroyGameObject(GameObjectID ID);
        void CleanupGameObjects();
    private:
        void VirtualOnDestroy() override;
        GameObjectManager() = default;

        GameObjectID m_nextGameObjectID = 0;

        std::unordered_map<GameObjectID, std::unique_ptr<GameObject>> m_gameObjects;
        std::queue< GameObject* > m_gameObjectsToCleanup;

    friend class Application;   // only Application can create a manager
    };
};