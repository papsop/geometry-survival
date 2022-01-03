#pragma once
#include "Transform.h"
#include "../../View/Renderables.h"

#include "../../Debug/Logger.h"
#include <type_traits>
#include <functional>

namespace Game
{
    class GameObject; 

    class IComponent
    {
    public:

        template<typename T>
        static uint32_t GetComponentID()
        {
            static uint32_t componentID = m_nextComponentID++;
            return componentID;
        }

        IComponent(GameObject& obj) : Owner(obj) {};
        virtual ~IComponent() = default;

        virtual void OnGameObjectChanged() = 0;
        virtual void Update(float dt) = 0;

        GameObject& Owner;
    protected:
        static uint32_t m_nextComponentID;
    };

    class IRenderableShapeComponent : public IComponent
    {
    public:
        IRenderableShapeComponent(GameObject& obj, int zIndex);
         
        ~IRenderableShapeComponent() override = default;

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