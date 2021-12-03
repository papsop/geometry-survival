#pragma once
#include "GameObject.h"
#include "Factories/GameObjectFactories.h"
#include <memory>
#include <unordered_map>

namespace Game
{
    class Scene
    {
    public:
        static uint32_t GetNewGameObjectID();

        void AddGameObject(std::shared_ptr<GameObject> go);
        void AddGameObjectViaFactory(const IGameObjectFactory& factory);

        void UpdateGameObjects(float dt);
        void RenderGameObjects();

    private:
        std::unordered_map<uint32_t, std::shared_ptr<GameObject>> m_gameObjects;
    };
};

