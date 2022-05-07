#pragma once
#include "Transform.h"
#include "../../View/Renderables.h"
#include "../../View/IViewStrategy.h"
#include "../../Core/ColliderData.h"
#include "../../Core/Serializing/SerializableField.h"

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
        using TRequiredFunc = std::function<void(GameObject&)>;

        IComponent(GameObject& obj) : Owner(obj) {};
        virtual ~IComponent() = default;

        virtual void OnCreate() {};
        virtual void Update(float dt) {};
        virtual void OnCollisionStart(GameObject* other) {};
        virtual void OnCollisionEnd(GameObject* other) {};
        
		GameObject& Owner;

        void CheckRequiredComponents()
        {
            if(m_requiredFunction != nullptr)
                m_requiredFunction(Owner);
        }

    protected:
        template<typename... Ts>
        struct requires_impl;

        template<typename T>
        struct requires_impl<T>;
        
        template<typename T, typename... Ts>
        struct requires_impl<T, Ts...>;

        // This function asserts required components on the Owner gameObject.
        // Function call gets stored and called every time a component
        // is removed from the owner
		template<typename... Ts>
		void SetRequiredComponents();

		template<typename T>
		void AddSerializableField(T value)
		{
            //auto val = static_cast<decltype(typename SerializableField(value)::type)>(value);
		}

        TRequiredFunc m_requiredFunction = nullptr;
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

#include "IComponent.inl"