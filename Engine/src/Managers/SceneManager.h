#pragma once
#include "../Core/Scene.h"

#include <vector>
#include "../Debug/IDebuggable.h"

namespace Engine
{
    class Application;

    class SceneManager
    {
    public:
        static SceneManager& Get();
        
        Scene& CreateScene();
        Scene& GetActiveScene();
        Scene& GetSceneByIndex(uint32_t index);

        // Loads all objects and adds them to already loaded ones
        void LoadSceneAdditively(uint32_t index);
        // Unloads all loaded objects and loads the ones from this scene
        void SetActiveScene(uint32_t index);


        // Unloads all objects from this particular scene
        void UnloadSceneObjects(uint32_t index);
        void UnloadAllScenes();

        ~SceneManager() = default;

        //void Debug(view::IViewStrategy* viewStrategy) override;

    private:
        SceneManager() = default;

        std::vector< std::unique_ptr<Scene> > m_scenes;
        uint32_t m_nextSceneID = 0;

    friend class Application;
    };
}


