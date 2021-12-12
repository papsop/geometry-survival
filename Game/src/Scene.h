#pragma once
#include "GameObject.h"
#include "Factories/GameObjectFactories.h"
#include <memory>
#include <unordered_set>

namespace Game
{
    class Scene
    {
    public:
        void AddGameObject(std::shared_ptr<GameObject> go);
        uint32_t AddGameObjectViaFactory(const IGameObjectFactory& factory);

        void UpdateGameObjects(float dt);
        void RenderGameObjects();

        void AddGameObject(uint32_t ID);
        void RemoveGameObject(uint32_t ID);

        std::unordered_set<uint32_t> GetSceneGameObjects() { return m_sceneEntities; };

    private:
        std::unordered_set<uint32_t> m_sceneEntities;
    };
};

