#pragma once
#include "GameObject.h"
#include "../Managers/GameObjectManager.h"
#include "../Debug/IDebuggable.h"

namespace Engine
{
    class Scene : public IDebuggable
    {
    public:
        Scene(uint32_t id);
        ~Scene() = default;

        void AddGameObject(GameObjectID id);
        void RemoveGameObject(GameObjectID id);
        void Load();
        void Unload();
        const uint32_t ID;
        bool IsLoaded() const { return m_isLoaded; }

        void Debug(view::IViewStrategy* viewStrategy) override;

    private:
        bool m_isLoaded = false;
        std::vector< GameObjectID > m_gameObjects; // maybe a scene graph later?

    };
};


