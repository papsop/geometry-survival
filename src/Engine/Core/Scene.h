#pragma once
#include "GameObject.h"
#include "../Managers/GameObjectManager.h"
#include "../Debug/IDebuggable.h"

#include "Events.h"
namespace Engine
{
    class SceneManager;
    class Scene : public IDebuggable, public IEventListener<GameObjectDeletedData>
    {
    public:
        enum class SceneType
        {
            AlwaysLoaded,   // scene is loaded while game is running (for game managers etc.)
            Discrete,       // only 1 active at a time
            Additive        // can be additively loaded
        };

        Scene(uint32_t id, SceneType sceneType);
        ~Scene() = default;

        void AddGameObject(GameObjectID id);
        void RemoveGameObject(GameObjectID id);
        
        const uint32_t c_ID;
        const SceneType c_SceneType;
        bool IsLoaded() const { return m_isLoaded; };

        void ReceiveEvent(const GameObjectDeletedData& eventData) override;
        void Debug(view::IViewStrategy* viewStrategy) override;

    private:
        void Load();
        void Unload();

        bool m_isLoaded = false;
        std::vector< GameObjectID > m_gameObjects; // maybe a scene graph later?

    friend class SceneManager;
    };
};


