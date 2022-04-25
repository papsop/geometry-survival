#include "Scene.h"
#include <string>
#include "../Utils/VectorUtils.h"

namespace Engine
{
    Scene::Scene(uint32_t id, SceneType sceneType)
        : c_ID(id)
        , c_SceneType(sceneType)
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
        }

    }

    void Scene::RemoveGameObject(GameObjectID id)
    {
        m_gameObjects.erase(std::remove(m_gameObjects.begin(), m_gameObjects.end(), id), m_gameObjects.end());
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
    }

    void Scene::ReceiveEvent(const GameObjectDeletedData& eventData)
    {
        RemoveGameObject(eventData.ID);
    }
    
    void Scene::SetState(std::unique_ptr<ISceneState> state)
    {
        m_state = std::move(state);
    }

    void Scene::Update(float dt)
    {
        if (m_state)
            m_state->Update(dt);
    }

    void Scene::Debug(view::IViewStrategy* viewStrategy)
    {
        if (!m_isLoaded) return;
        Transform t;
        t.Position = math::Vec2(500.0f, 0.0f);
        view::Text text(&t);
        text.Size = 12;
        text.Color = sf::Color::Green;
        std::string val = "Active GameObjects in scene: " + std::to_string(m_gameObjects.size());
        text.Value = val.c_str();
        viewStrategy->Render(text);
    }
};