#pragma once
#include <array>
#include <stack>
#include <unordered_map>
#include <vector>

#include "../Core/Events.h"
#include "../Core/GameObject/GameObject.h"
#include "../Debug/IDebuggable.h"
#include "IManager.h"

namespace Engine {
class GameObjectManager : public IManager, public IDebuggable {
 public:
  enum E_PoolingBucketType {
    ENEMY,
    BULLET,
    EXPERIENCE,
    COUNT,
  };

  ~GameObjectManager() = default;

  static GameObjectManager& Get();

  GameObject* CreateGameObject(const char* name, GameObjectTag tag, const ITransform::TransformDefinition& transformDef);
  GameObject* GetGameObjectByID(GameObjectID ID);
  std::vector<GameObject*> GetGameObjectsByTag(GameObjectTag tag);

  void Update(float dt) override;
  void DestroyGameObject(GameObjectID ID);
  void DestroyAllGameObjects();
  void CleanupGameObjects();
  void InitializeGameObjects();

  void Debug(VisualDebugContext& debugContext) override;

  void ReleasePooledObject(E_PoolingBucketType type, GameObject* obj);
  GameObject* GetPooledObject(E_PoolingBucketType type);  // might return nullptr if no objects available

 protected:
  void VirtualOnInit() override;
  void VirtualOnDestroy() override;

 private:
  GameObjectManager() = default;

  void DebugDraw_ExpandGameObject(GameObject* obj);

  GameObjectID m_nextGameObjectID = 0;

  std::unordered_map<GameObjectID, std::unique_ptr<GameObject>> m_gameObjects;
  std::queue<GameObject*> m_gameObjectsToCleanup;
  std::queue<GameObject*> m_gameObjectsToInitialize;
  std::array<std::stack<GameObject*>, static_cast<size_t>(E_PoolingBucketType::COUNT)> m_poolingBuckets;

  friend class Application;  // only Application can create a manager
};
};  // namespace Engine
