#pragma once
#include "../Debug/Logger.h"
#include "../Components/Core.h"
#include "../Components/Physics.h"
#include "../Components/View.h"
#include <unordered_map>
#include <map>
#include <queue>
#include <memory>
#include <assert.h>
#include <type_traits>

namespace Engine
{
    class GameObject
    {
    public:
        // Components Management
        template<typename T>
        bool HasComponent()
        {
            static_assert(std::is_base_of<IComponent, T>::value, "Not derived from IComponent");
            auto compID = IComponent::GetComponentID<T>();
            return m_components.find(compID) != m_components.end();
        }

        template<typename T, typename ... Args>
        void AddComponent(Args&& ... args)
        {
            static_assert(std::is_base_of<IComponent, T>::value, "Not derived from IComponent");
            if (!HasComponent<T>())
            {
                m_components[IComponent::GetComponentID<T>()] = std::make_unique<T>(*this ,std::forward<Args>(args) ...);
                NotifyComponents();
            }
            else LOG_WARN("AddComponent: GO %d already has Component '%s', ignoring this function call", ID, typeid(T).name());
        }

        template<typename T>
        void RemoveComponent()
        {
            static_assert(std::is_base_of<IComponent, T>::value, "Not derived from IComponent");
            if(HasComponent<T>())
                m_components.erase(IComponent::GetComponentID<T>());

            NotifyComponents();
        }

        template<typename T>
        T* GetComponent()
        {
            static_assert(std::is_base_of<IComponent, T>::value, "Not derived from IComponent");
            if (HasComponent<T>())
                return dynamic_cast<T*>(m_components[IComponent::GetComponentID<T>()].get());
            else
                return nullptr;
        }

        // --------------------------
        GameObject(uint32_t id, const char* debugName);
        ~GameObject() = default;

        const uint32_t ID;
        const char* DebugName;
        Transform& GetTransform() {   return m_transform; }

        void Destroy() { m_shouldDestroy = true; }
        void SetActive(bool a) { m_isActive = a; }

        bool ShouldDestroy() const { return m_shouldDestroy; }
        bool IsActive() const { return m_isActive; }
        bool ShouldUpdate() const { return m_isActive && !m_shouldDestroy; }

    private:
        std::unordered_map<uint32_t, std::unique_ptr<IComponent>> m_components = {};
        bool m_shouldDestroy = false;
        bool m_isActive = false;
        Transform m_transform;

        void NotifyComponents();
    };
};

