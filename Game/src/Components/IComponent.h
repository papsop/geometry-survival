#pragma once
#include <type_traits>

namespace Game
{
    class GameObject; 

    class IComponent
    {
    public:
        template<typename T>
        static constexpr bool is_derived() { return std::is_base_of<IComponent, T>::value; }

        IComponent(GameObject& obj) : m_owner(obj) {};
        virtual ~IComponent() = default;

        virtual void Update(float dt) = 0;
    protected:
        GameObject& m_owner;
    };

    class IRenderableComponent
    {
    public:
        template<typename T>
        static constexpr bool is_derived() { return std::is_base_of<IRenderableComponent, T>::value; }

        IRenderableComponent(GameObject& obj) : m_owner(obj) {};
        virtual ~IRenderableComponent() = default;

        virtual void Render() = 0;
    protected:
        GameObject& m_owner;
    };
};