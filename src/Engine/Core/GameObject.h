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
        bool HasComponent()
        {
            static_assert(std::is_base_of<IComponent, T>::value, "Not derived from IComponent");
            auto compID = IdGenerator<IComponent>::GetID<T>();
            return m_components.find(compID) != m_components.end();
        }

        template<typename T, typename ... Args>
        void AddComponent(Args&& ... args)
        {
            static_assert(std::is_base_of<IComponent, T>::value, "Not derived from IComponent");
            if (!HasComponent<T>())
            {
                auto ID = IdGenerator<IComponent>::GetID<T>();
                m_components[ID] = std::make_unique<T>(*this ,std::forward<Args>(args) ...);
                m_components[ID]->OnCreate();
            }
            else LOG_WARN("AddComponent: GO %d already has Component '%s', ignoring this function call", c_ID, typeid(T).name());
        }

        template<typename T>
        void RemoveComponent()
        {
            static_assert(std::is_base_of<IComponent, T>::value, "Not derived from IComponent");
            if (HasComponent<T>())
            {
                auto ID = IdGenerator<IComponent>::GetID<T>();
                m_components.erase(ID);
            }
        }

        template<typename T>
        T* GetComponent()
        {
            static_assert(std::is_base_of<IComponent, T>::value, "Not derived from IComponent");
            if (HasComponent<T>())
            {
                auto ID = IdGenerator<IComponent>::GetID<T>();
                return dynamic_cast<T*>(m_components[ID].get());
            }
            else
                return nullptr;
        }

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

