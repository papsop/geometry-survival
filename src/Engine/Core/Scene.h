#pragma once
#include "GameObject.h"
#include "../Managers/GameObjectManager.h"
#include "../Debug/IDebuggable.h"
#include "StateMachine/IState.h"

#include "Events.h"
namespace Engine
{
    class SceneManager;
    class SceneSerializer;

    class Scene : public IDebuggable, public IEventListener<E_GameObjectDeleted>
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

        void CreateGameObject();
        void AddGameObject(GameObjectID id);
        void RemoveGameObject(GameObjectID id);
        
        const uint32_t c_ID;
        const SceneType c_SceneType;
        bool IsLoaded() const { return m_isLoaded; };
        
        void SetState(std::unique_ptr<ISceneState> state);

        void ReceiveEvent(const E_GameObjectDeleted& eventData) override;
        void Debug(view::IViewStrategy* viewStrategy) override;
        
    private:
        void Load();
        void Unload();
        void Update(float dt);

        bool m_isLoaded = false;
        std::vector< GameObjectID > m_gameObjects; // maybe a scene graph later?
        std::unique_ptr< ISceneState > m_state;

    friend class SceneManager;
    friend class SceneSerializer;
    };
};


