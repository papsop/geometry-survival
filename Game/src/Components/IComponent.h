#pragma once
#include "Transform.h"
#include "../Singletons/InputManager.h"
#include "../Singletons/RenderManager.h"
#include "../utils.h"

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

        IComponent(GameObject& obj) : m_owner(obj) {};
        virtual ~IComponent() = default;

        virtual void OnGameObjectChanged() = 0;
        virtual void Update(float dt) = 0;
    protected:
        static uint32_t m_nextComponentID;
        GameObject& m_owner;
    };

    class IRenderableShape
    {
    public:
        IRenderableShape() = default;
        ~IRenderableShape() = default;

        virtual const view::Shape& GetRenderableShape() = 0;

    protected:
        view::Shape m_renderableShape;
    };

    class IRenderableText
    {
    public:
        IRenderableText() = default;
        ~IRenderableText() = default;

        std::string GetRenderableText() const { return m_renderableText; };
    private:
        std::string m_renderableText;
    };

};