#pragma once
#include "Components/IComponent.h"
#include "Components/RenderComponent.h"

#include <unordered_map>
#include <memory>
#include <assert.h>

namespace Game
{
    class GameObject
    {
    public:
        // Components Management
        template<typename T>
        bool HasComponent() { return m_components.find(typeid(T).name()) != m_components.end(); }

        template<typename T>
        void AddComponent(T component) 
        {
            assert(!HasComponent<T>() && "GameObject already has this component");
            m_components[typeid(T).name()] = std::make_shared<T>(component);

            if (typeid(T).name() == typeid(RenderComponent).name())
                m_isRenderable = true;
        }
        
        template<typename T>
        std::shared_ptr<T> GetComponent()
        {
            auto component = m_components[typeid(T).name()];
            return std::static_pointer_cast<T>(component);
        }

        template<typename T>
        void RemoveComponent()
        {
            if (HasComponent<T>())
                m_components.erase(typeid(T).name());

            if (typeid(T).name() == typeid(RenderComponent).name())
                m_isRenderable = false;
        }
        // --------------------------
        void Destroy() { m_shouldDestroy = true; }
        bool ShouldDestroy() { return m_shouldDestroy; }
        bool IsRenderable() { return m_isRenderable; }

        void Update(float dt);

        void Render();

    private:
        std::unordered_map<const char*, std::shared_ptr<IComponent>> m_components;
        bool m_shouldDestroy = false;
        bool m_isRenderable = false;
    };
};


