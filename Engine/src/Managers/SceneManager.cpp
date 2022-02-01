#include "SceneManager.h"
#include "../Debug/Logger.h"
#include "../Application.h"

namespace Engine
{
    SceneManager& SceneManager::Get()
    {
        return Application::Instance().GetSceneManager();
    }

    Scene& SceneManager::CreateScene()
    {
        m_scenes.emplace_back(std::make_unique<Scene>(m_nextSceneID++));
        return *m_scenes[m_nextSceneID - 1].get();
    }

    Scene& SceneManager::GetSceneByIndex(uint32_t index)
    {
        DD_ASSERT(index < m_scenes.size(), "Scene with ID '%d' doesn't exist", index);
        return *m_scenes[index].get();
    }

    void SceneManager::LoadSceneAdditively(uint32_t index)
    {
        auto& scene = GetSceneByIndex(index);
        scene.Load();
    }

    void SceneManager::SetActiveScene(uint32_t index)
    {
        UnloadAllScenes();
        LoadSceneAdditively(index);
    }

    void SceneManager::UnloadSceneObjects(uint32_t index)
    {
        auto& scene = GetSceneByIndex(index);
        scene.Unload();
    }

    void SceneManager::UnloadAllScenes()
    {
        for (auto&& s : m_scenes)
            if (s->IsLoaded())
                s->Unload();
    }

    //void SceneManager::Debug(view::IViewStrategy* viewStrategy)
    //{
    //    Transform t;
    //    t.Position = sf::Vector2f(500.0f, 13.0f);
    //    view::Text text(t);
    //    text.Size = 12;
    //    text.Color = sf::Color::Blue;
    //    text.Value = "Scenes:";
    //    viewStrategy->Render(text);

    //    for(size_t i=0; i< m_scenes.size();++i)
    //    {
    //        Transform t;
    //        t.Position = sf::Vector2f(500.0f, 13.0f * (i+1));
    //        view::Text text(t);
    //        text.Size = 12;
    //        text.Color = (m_scenes[i]->IsLoaded()) ? sf::Color::Green : sf::Color::Red;
    //        text.Value = m_scenes[i]->ID;
    //        viewStrategy->Render(text);
    //    }
    //}
}