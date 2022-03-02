#pragma once
#include "Transform.h"
#include "../../View/Renderables.h"
#include "../../View/IViewStrategy.h"

#include "../../Debug/Logger.h"
#include <stdint.h>
#include <type_traits>
#include <functional>
#include <iostream>

namespace Engine
{
    class GameObject; 

    class IComponent
    {
    public:
        IComponent(GameObject& obj) : Owner(obj) {};
        virtual ~IComponent() = default;

        virtual void Update(float dt) = 0;
        virtual void OnCollision(GameObject& other){};

        GameObject& Owner;
    protected:

        // =================
        // Requires template
        //  - for asserting required components
        // =================
        template<typename First, typename... Args>
        void Requires()
        {
            bool hasComponent = Owner.HasComponent<First>();
            DD_ASSERT(hasComponent, "IComponent::Required asserted");

            const int size = sizeof...(Args);
            if constexpr (size > 0)
                Requires<Args...>();
        }
    };


    // Physics

    class IColliderComponent : public IComponent
    {
    public:
        enum class LayerType // worth it?
        {
            GameplayArea,

            COUNT // always last
        };

        IColliderComponent(GameObject& obj, LayerType layer)
            : IComponent(obj)
            , m_layer(layer)
        {}
        ~IColliderComponent() override = default;        
        
        void SetRelativePosition(sf::Vector2f position);
        sf::Vector2f GetRelativePosition() const;
        sf::Vector2f GetAbsolutePosition() const;
        LayerType GetLayer() { return m_layer; };

    private:
        sf::Vector2f m_relativePosition;
        LayerType m_layer;
    };


    // Views
    class IRenderableShapeComponent : public IComponent
    {
    public:
        IRenderableShapeComponent(GameObject& obj, int zIndex);
         
        ~IRenderableShapeComponent() = default;

        virtual const view::Shape& GetRenderableShape() = 0;
        const int ZIndex;
    protected:
        Transform& m_ownerTransform;
    };

    class IRenderableTextComponent : public IComponent
    {
    public:
        IRenderableTextComponent(GameObject& obj);

        ~IRenderableTextComponent() override = default;

        virtual const view::Text& GetRenderableText() = 0;
    protected:
        Transform& m_ownerTransform;
    };
};