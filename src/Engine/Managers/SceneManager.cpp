#include "SceneManager.h"
#include "../Debug/Logger.h"
#include "../Application.h"
#include "GameObjectManager.h"

#include <string>
namespace Engine
{
    SceneManager& SceneManager::Get()
    {
        return Application::Instance().GetSceneManager();
    }

    void SceneManager::LoadSceneDestroyPrevious(const IScene& scene)
    {
      // Delete all the existing gameObjects
      GameObjectManager::Get().DestroyAllGameObjects();

      // Instantiate new scene
      scene.InstantiateObjects();
    }

}