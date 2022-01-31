#include "Scene.h"

namespace Engine
{
    Scene::Scene(uint32_t id)
        : ID(id)
    {
    }

    void Scene::AddGameObject(GameObject* obj)
    {
        if (m_isLoaded) obj->SetActive(m_isLoaded);
        m_gameObjects.emplace_back(obj);
        LOG_INFO("GameObject %d added to Scene %d", obj->ID, ID);
    }

    void Scene::Load()
    {
        for (auto go : m_gameObjects)
            go->SetActive(true);
        m_isLoaded = true;
        LOG_INFO("Scene %d loaded, number of objects: %d", ID, m_gameObjects.size());
    }

    void Scene::Unload()
    {
        for (auto go : m_gameObjects)
            go->SetActive(false);
        m_isLoaded = false;
        LOG_INFO("Scene %d unloaded", ID);
    }
};