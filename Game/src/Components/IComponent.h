#pragma once
#include "../Singletons/SingletonManager.h"

#include <type_traits>
#include <functional>

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

        virtual void Init() = 0;
        virtual void Update(float dt) = 0;
    protected:
        GameObject& m_owner;
    };

    class IRenderableComponent
    {
    public:
        template<typename T>
        static constexpr bool is_derived() { return std::is_base_of<IRenderableComponent, T>::value; }

        IRenderableComponent(GameObject& obj, int zIndex) : m_owner(obj), m_zIndex(zIndex){};
        virtual ~IRenderableComponent() = default;

        virtual void Init() = 0;
        virtual void Render() = 0;

        const int GetZIndex() const { return m_zIndex; }
    protected:
        GameObject& m_owner;
        const int m_zIndex; // should be changeable?
    };
};