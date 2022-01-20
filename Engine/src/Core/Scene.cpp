#include "Scene.h"

namespace Engine
{
    Scene::Scene(uint32_t id)
        : ID(id)
    {
    }

    void Scene::AddGameObject(GameObject* obj)
    {
        m_gameObjects.emplace_back(obj);
    }

    void Scene::Load()
    {
        for (auto go : m_gameObjects)
            go->SetActive(true);
    }

    void Scene::Unload()
    {
        for (auto go : m_gameObjects)
            go->SetActive(false);
    }
};