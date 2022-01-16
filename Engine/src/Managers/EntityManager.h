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

        std::weak_ptr<GameObject> CreateEntityReturnEntity(const char* name="Unknown");
        uint32_t                  CreateEntityReturnID(const char* name="Unknown");

        std::weak_ptr<GameObject> GetEntityByID(uint32_t ID);
    private:
        EntityManager() = default;

        uint32_t m_nextEntityID = 0;

        std::unordered_map<uint32_t, std::shared_ptr<GameObject>> m_entities;

    friend class Application;   // only Application can create a manager
    };
};


