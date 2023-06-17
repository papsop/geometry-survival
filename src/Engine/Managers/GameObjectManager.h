#pragma once
#include "IManager.h"
#include "../Core/GameObject/GameObject.h"
#include "../Core/Events.h"
#include "../Debug/IDebuggable.h"

#include <vector>
#include <unordered_map>

namespace Engine
{

    class GameObjectManager : public IManager, public IDebuggable
    {
    public:
      ~GameObjectManager() = default;

      static GameObjectManager& Get();

      GameObject* CreateGameObject(const char* name, GameObjectTag tag, const ITransform::TransformDefinition & transformDef);
      GameObject* GetGameObjectByID(GameObjectID ID);
      std::vector<GameObject*> GetGameObjectsByTag(GameObjectTag tag);

      void Update(float dt) override;
      void DestroyGameObject(GameObjectID ID);
      void DestroyAllGameObjects();
			void CleanupGameObjects();
			void InitializeGameObjects();

      void Debug(VisualDebugContext& debugContext) override;

    protected:
      void VirtualOnInit() override;
      void VirtualOnDestroy() override;

    private:
      GameObjectManager() = default;

      void DebugDraw_ExpandGameObject(GameObject* obj);

      GameObjectID m_nextGameObjectID = 0;

      std::unordered_map<GameObjectID, std::unique_ptr<GameObject>> m_gameObjects;
			std::queue< GameObject* > m_gameObjectsToCleanup;
			std::queue< GameObject* > m_gameObjectsToInitialize;

    friend class Application;   // only Application can create a manager

    };
};