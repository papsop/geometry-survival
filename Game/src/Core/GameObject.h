#pragma once
#include "../Debug/Logger.h"
#include "../Components/AllComponents.h"
#include <unordered_map>
#include <map>
#include <queue>
#include <memory>
#include <assert.h>
#include <type_traits>

namespace Game
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
                m_components[IComponent::GetComponentID<T>()] = std::make_shared<T>(std::forward<Args>(args) ...);
                NotifyComponents();
            }
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
        std::weak_ptr<T> GetComponent()
        {
            static_assert(std::is_base_of<IComponent, T>::value, "Not derived from IComponent");
            if (HasComponent<T>())
                return std::static_pointer_cast<T>(m_components[IComponent::GetComponentID<T>()]);
            else
                return {};
        }


        // --------------------------
        GameObject(uint32_t id, const char* debugName);
        ~GameObject() {};

        const uint32_t ID;
        const char* DebugName;
        Transform& GetTransform() {   return m_transform; }

//        std::unordered_map<uint32_t, std::shared_ptr<IComponent>> GetAllComponents() { return m_components; }

        void Destroy() { m_shouldDestroy = true; }
        bool ShouldDestroy() const { return m_shouldDestroy; }

    private:
        std::unordered_map<uint32_t, std::shared_ptr<IComponent>> m_components = {};
        bool m_shouldDestroy = false;
        Transform m_transform;

        void NotifyComponents();

        template<typename T>
        void UpdateComponentIfExists(float dt)
        {
            static_assert(std::is_base_of<IComponent, T>::value, "Not derived from IComponent");
            if (HasComponent<T>())
                m_components[IComponent::GetComponentID<T>()]->Update(dt);
        }
    };
};

