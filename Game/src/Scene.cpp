#include "Scene.h"

namespace Game
{
    uint32_t Scene::GetNewGameObjectID()
    {
        static uint32_t ID = 0;
        return ID++;
    }

    void Scene::AddGameObject(std::shared_ptr<GameObject> go)
    {
        m_gameObjects[go->ID] = go;
    }

    std::weak_ptr<GameObject> Scene::AddGameObjectViaFactory(const IGameObjectFactory& factory)
    {
        auto createdObj = factory.CreateGameObject();
        AddGameObject(createdObj);
        return createdObj;
    }

    void Scene::UpdateGameObjects(float dt)
    {
        for (auto gameObject : m_gameObjects)
            gameObject.second->Update(dt);
    }
    void Scene::RenderGameObjects()
    {
        for (auto gameObject : m_gameObjects)
            gameObject.second->Render();
    }
};