#pragma once
#include "../Core/GameObject.h"
#include <unordered_map>

namespace Engine
{
    class EntityManager
    {
    public:
        ~EntityManager() = default;

        static EntityManager& Get();

        GameObject* CreateEntity(const char* name="Unknown");

        GameObject* GetEntityByID(uint32_t ID);

        void DestroyEntity(uint32_t ID);
        void CleanupEntities();

    private:
        EntityManager() = default;

        uint32_t m_nextEntityID = 0;

        std::unordered_map<uint32_t, std::unique_ptr<GameObject>> m_entities;
        std::queue< GameObject* > m_entitiesToCleanup;

    friend class Application;   // only Application can create a manager
    };
};


