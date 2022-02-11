#pragma once
#include "Transform.h"
#include "../../View/Renderables.h"
#include "../../View/IViewStrategy.h"

#include "../../Debug/Logger.h"
#include <stdint.h>
#include <type_traits>
#include <functional>

namespace Engine
{
    class GameObject; 

    class IComponent
    {
    public:
        IComponent(GameObject& obj) : Owner(obj) {};
        virtual ~IComponent() = default;

        virtual void OnGameObjectChanged() = 0;
        virtual void Update(float dt) = 0;

        GameObject& Owner;
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