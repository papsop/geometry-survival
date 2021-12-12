#pragma once
#include "../Singletons/InputManager.h"
#include "../Singletons/RenderManager.h"

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

    //class IRenderableComponent
    //{
    //public:
    //    template<typename T>
    //    static constexpr bool is_derived() { return std::is_base_of<IRenderableComponent, T>::value; }

    //    IRenderableComponent(GameObject& obj, int zIndex) 
    //        : m_owner(obj)
    //        , m_zIndex(zIndex)
    //        , m_renderManager(SingletonManager::Instance().GetRenderManager())
    //    {};

    //    virtual ~IRenderableComponent() = default;

    //    virtual void Init() = 0;
    //    virtual void Render() = 0;

    //    const int GetZIndex() const { return m_zIndex; }
    //protected:
    //    GameObject& m_owner;
    //    RenderManager* m_renderManager;
    //    const int m_zIndex; // should be changeable?
    //};
};