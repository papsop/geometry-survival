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
        static uint32_t GetNewGameObjectID()
        {
            static uint32_t ID = 0;
            return ID++;
        }

        void AddGameObject(std::shared_ptr<GameObject> go)
        {
            m_gameObjects[go->ID] = go;
        }

        void AddGameObjectViaFactory(const IGameObjectFactory &factory)
        {
            AddGameObject(factory.CreateGameObject());
        }

        void UpdateGameObjects(float dt)
        {
            for (auto gameObject : m_gameObjects)
                gameObject.second->Update(dt);
        }
        void RenderGameObjects()
        {
            for (auto gameObject : m_gameObjects)
                gameObject.second->Render();
        }
    private:
        std::unordered_map<uint32_t, std::shared_ptr<GameObject>> m_gameObjects;
    };
};

