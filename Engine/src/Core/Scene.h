#pragma once
#include "GameObject.h"
#include "../Managers/GameObjectManager.h"
#include "../Debug/IDebuggable.h"

#include "Events.h"
namespace Engine
{
    class Scene : public IDebuggable, public IEventListener<GameObjectDeletedData>
    {
    public:
        Scene(uint32_t id);
        ~Scene() = default;

        void AddGameObject(GameObjectID id);
        void RemoveGameObject(GameObjectID id);
        void Load();
        void Unload();
        const uint32_t ID;
        bool IsLoaded() const { return m_isLoaded; };

        void Receive(const GameObjectDeletedData& eventData) override;
        void Debug(view::IViewStrategy* viewStrategy) override;

    private:
        bool m_isLoaded = false;
        std::vector< GameObjectID > m_gameObjects; // maybe a scene graph later?

    };
};


