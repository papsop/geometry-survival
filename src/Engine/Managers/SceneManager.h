#pragma once
#include "IManager.h"
#include "../Core/Scene/IScene.h"

#include <vector>
#include "../Debug/IDebuggable.h"

namespace Engine
{
    class Application;

    class SceneManager : public IManager
    {
    public:
        static SceneManager& Get();
        
        ~SceneManager() = default;

        void LoadSceneDestroyPrevious(const IScene& scene);

        template<
          typename T,
          typename = std::enable_if_t<std::is_base_of_v<IScene, T>>
        >
        void LoadSceneDestroyPreviousDeferred()
        {
          Engine::Application::Instance().AddEndOfFrameDeferredAction(
            [=]()
            {
              Engine::SceneManager::Get().LoadSceneDestroyPrevious(T());
            }
          );
        }

    private:
        SceneManager() = default;

    friend class Application;
    };

}
