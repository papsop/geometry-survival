#include "Scene.h"

namespace Game
{
    void Scene::AddGameObject(uint32_t ID)
    {
        m_sceneEntities.insert(ID);
    }

    void Scene::RemoveGameObject(uint32_t ID)
    {
        m_sceneEntities.erase(ID);
    }

    uint32_t Scene::AddGameObjectViaFactory(const IGameObjectFactory& factory)
    {
        auto createdID = factory.CreateGameObject();
        AddGameObject(createdID);
        return createdID;
    }

    void Scene::UpdateGameObjects(float dt)
    {
        //for (auto gameObject : m_gameObjects)
        //    gameObject.second->Update(dt);
    }
    void Scene::RenderGameObjects()
    {
        //for (auto gameObject : m_gameObjects)
        //    gameObject.second->Render();
    }
};