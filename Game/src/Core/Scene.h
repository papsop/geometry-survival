#pragma once
#include "GameObject.h"
#include "../Factories/GameObjectFactories.h"
#include <memory>
#include <unordered_set>

namespace Game
{
    class Scene
    {
    public:
        void AddGameObject(uint32_t id);
        uint32_t AddGameObjectViaFactory(const IGameObjectFactory& factory);

        void UpdateGameObjects(float dt);
        void RenderGameObjects();

        void RemoveGameObject(uint32_t ID);

        std::unordered_set<uint32_t> GetSceneGameObjects() { return m_sceneEntities; };

    private:
        std::unordered_set<uint32_t> m_sceneEntities;
    };
};

