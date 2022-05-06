#pragma once
#include "../Debug/Logger.h"
#include "../Components/Core.h"
#include "../Components/Physics.h"
#include "../Components/View.h"
#include "../Utils/IdGenerator.h"

#include <unordered_map>
#include <map>
#include <queue>
#include <memory>
#include <assert.h>
#include <type_traits>

namespace Engine
{
    typedef uint32_t GameObjectID;

    class EntityManager;
    class Scene;

    class GameObject
    {
    public:

        enum class FilterTag
        {
            PLAYER,
            ENEMY,
            PROJECTILE,
            OBSTACLE,
            UI,

            COUNT, // always last
        };
        // Components Management
        template<typename T>
        bool HasComponent();

        template<typename T, typename ... Args>
        void AddComponent(Args&& ... args);

        template<typename T>
        void RemoveComponent();

        template<typename T>
        T* GetComponent();

        // --------------------------
        GameObject(uint32_t id, FilterTag tag, const char* debugName);
        ~GameObject() = default;

        const uint32_t c_ID;
        const char* c_DebugName;
        const FilterTag c_Tag;

        Transform& GetTransform() {   return m_transform; }

        void OnCollisionStart(GameObject* other);
        void OnCollisionEnd(GameObject* other);

        void Destroy();
        void SetActive(bool a) { m_isActive = a; }

        bool ShouldDestroy() const { return m_shouldDestroy; }
        bool IsActive() const { return m_isActive; }
        bool ShouldUpdate() const { return m_isActive && !m_shouldDestroy; }

        void SetScene(Scene* scene) { m_scene = scene; }
        Scene& GetScene() { return *m_scene; }

    private:
        std::unordered_map<uint32_t, std::unique_ptr<IComponent>> m_components = {};
        bool m_shouldDestroy = false;
        bool m_isActive = false;

        Transform m_transform;
        Scene* m_scene;

        friend class GameObjectManager;
    };
};

#include "GameObject.inl"