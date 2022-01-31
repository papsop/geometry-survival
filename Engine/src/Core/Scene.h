#pragma once
#include "GameObject.h"

namespace Engine
{
    class Scene
    {
    public:
        Scene(uint32_t id);
        ~Scene() = default;

        void AddGameObject(GameObject* obj);
        void Load();
        void Unload();
        const uint32_t ID;
        bool IsLoaded() const { return m_isLoaded; }

    private:
        bool m_isLoaded = false;
        std::vector<GameObject*> m_gameObjects; // maybe a scene graph later?

    };
};


