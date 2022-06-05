#include "SceneManager.h"
#include "../Debug/Logger.h"
#include "../Application.h"
#include "../Core/Scene/Scene.h"
#include "../Core/Serializing/SceneSerializer.h"

#include <string>
namespace Engine
{
    SceneManager& SceneManager::Get()
    {
        return Application::Instance().GetSceneManager();
    }

    Scene& SceneManager::CreateScene()
    {
        m_scenes.emplace_back(std::make_unique<Scene>(m_nextSceneID++, Scene::SceneType::Discrete));
        return *m_scenes[m_nextSceneID - 1].get();
    }

    Scene& SceneManager::GetSceneByIndex(uint32_t index)
    {
        DD_ASSERT(index < m_scenes.size(), "Scene with ID '%d' doesn't exist", index);
        return *m_scenes[index].get();
    }

    void SceneManager::LoadSceneByIndex(uint32_t index)
    {
        auto& scene = GetSceneByIndex(index);
        if (scene.IsLoaded()) return;
        
        if (scene.c_SceneType == Scene::SceneType::Discrete)
        {
            UnloadAllScenes();
        }
        scene.Load();
    }

    void SceneManager::UnloadSceneByIndex(uint32_t index)
    {
        auto& scene = GetSceneByIndex(index);
        scene.Unload();
    }

    void SceneManager::UnloadAllScenes()
    {
        for (auto& s : m_scenes)
            if (s->IsLoaded())
                s->Unload();
    }

    void SceneManager::Update(float dt)
    {
        for (auto& s : m_scenes)
            if (s->IsLoaded())
                s->Update(dt);
    }

    void SceneManager::SaveAllScenes()
    {
        for (auto& scene : m_scenes)
        {
			SceneSerializer s(*scene);
			s.Serialize("assets/scenes/scene" + std::to_string(scene->ID) + ".yaml");
        }
    }
}