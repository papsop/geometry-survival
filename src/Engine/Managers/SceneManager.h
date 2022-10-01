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

    private:
        SceneManager() = default;

    friend class Application;
    };
}
