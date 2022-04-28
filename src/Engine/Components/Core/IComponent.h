#pragma once
#include "Transform.h"
#include "../../View/Renderables.h"
#include "../../View/IViewStrategy.h"
#include "../../Core/ColliderData.h"

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

        virtual void OnCreate() {};
        virtual void Update(float dt) {};
        virtual void OnCollisionStart(GameObject& other) {};
        virtual void OnCollisionEnd(GameObject& other) {};

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

            //const int size = sizeof...(Args);
            //if constexpr (size > 0)
            //    Requires<Args...>();
        }
    };

    // Views
    class IRenderableShapeComponent : public IComponent
    {
    public:
        IRenderableShapeComponent(GameObject& obj, view::RENDERABLE_TYPE renderableType, int zIndex);
         
        ~IRenderableShapeComponent() = default;

        const view::Renderable& GetRenderable() { return m_renderable; };
        const int ZIndex;
    protected:
        view::Renderable m_renderable;
        Transform m_renderableTransform;
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