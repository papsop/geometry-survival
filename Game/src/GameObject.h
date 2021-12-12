#pragma once
#include "Components/IComponent.h"
#include "Components/Transform.h"

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
            auto compID = IComponent::GetComponentID<T>();
            return m_components.find(compID) != m_components.end();
        }

        template<typename T, typename ... Args>
        void AddComponent(Args&& ... args)
        {
            m_components[IComponent::GetComponentID<T>()] = std::make_shared<T>(std::forward<Args>(args) ...);

            NotifyComponents();
        }

        template<typename T>
        void RemoveComponent()
        {
            if(HasComponent<T>())
                m_components.erase(IComponent::GetComponentID<T>());

            NotifyComponents();
        }

        template<typename T>
        std::weak_ptr<T> GetComponent()
        {
            if (HasComponent<T>())
                return std::static_pointer_cast<T>(m_components[IComponent::GetComponentID<T>()]);
            else
                return {};
        }


        // --------------------------
        GameObject(uint32_t id, const char* debugName) : ID(id), DebugName(debugName), m_transform() {};
        ~GameObject() {};

        const uint32_t ID;
        const char* DebugName;
        Transform& GetTransform() { return m_transform; }

        void Update(float dt);
        void Render();

        void Destroy() { m_shouldDestroy = true; }
        bool ShouldDestroy() const { return m_shouldDestroy; }

    private:
        std::unordered_map<uint32_t, std::shared_ptr<IComponent>> m_components = {};
        //std::map<const char*, std::shared_ptr<IRenderableComponent>> m_renderableComponents;
        bool m_shouldDestroy = false;
        Transform m_transform;

        void NotifyComponents();

        template<typename T>
        void UpdateComponentIfExists(float dt)
        {
            if (HasComponent<T>())
                m_components[IComponent::GetComponentID<T>()]->Update(dt);
        }
    };
};

