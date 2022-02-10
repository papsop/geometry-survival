#include "Scene.h"
#include <string>

namespace Engine
{
    Scene::Scene(uint32_t id)
        : ID(id)
    {
    }

    void Scene::AddGameObject(GameObjectID id)
    {
        auto entity = GameObjectManager::Get().GetGameObjectByID(id);
        if (entity != nullptr)
        {
            if (m_isLoaded) entity->SetActive(m_isLoaded);
            m_gameObjects.emplace_back(id);
            entity->SetScene(this);
            LOG_DEBUG("Entity '%d' added to Scene '%d'", entity->ID, ID);
        }

    }

    void Scene::Load()
    {
        for (auto id : m_gameObjects)
        {
            auto entity = GameObjectManager::Get().GetGameObjectByID(id);
            if (entity != nullptr)
            {
                entity->SetActive(true);
            }
        }
        m_isLoaded = true;
        LOG_INFO("Scene ID '%d' LOADED, number of objects: %d", ID, m_gameObjects.size());
    }

    void Scene::Unload()
    {
        for (auto id : m_gameObjects)
        {
            auto entity = GameObjectManager::Get().GetGameObjectByID(id);
            if (entity != nullptr)
            {
                entity->SetActive(false);
            }
        }
        m_isLoaded = true;
        LOG_INFO("Scene ID '%d' UNLOADED, number of objects: %d", ID, m_gameObjects.size());
    }

    //void Scene::GameObjectDeletedListener(GameObjectID id)
    //{
    //    m_gameObjects.erase(std::remove(m_gameObjects.begin(), m_gameObjects.end(), id), m_gameObjects.end());
    //}

    void Scene::Debug(view::IViewStrategy* viewStrategy)
    {
        if (!m_isLoaded) return;
        Transform t;
        t.Position = sf::Vector2f(500.0f, 0.0f);
        view::Text text(t);
        text.Size = 12;
        text.Color = sf::Color::Green;
        std::string val = "Active GameObjects in scene: " + std::to_string(m_gameObjects.size());
        text.Value = val.c_str();
        viewStrategy->Render(text);
    }
};