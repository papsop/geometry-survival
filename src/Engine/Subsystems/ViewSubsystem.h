#pragma once
#include "../Components/View.h"
#include "../View/IViewStrategy.h"
#include "../Debug/IDebuggable.h"

#include <vector>
#include <set>
#include <memory>

namespace Engine
{
    class SubsystemManager;

    class ViewSubsystem
    {
    public:
        ~ViewSubsystem();

        void RegisterComponent(IRenderableShapeComponent* component);
        void RegisterComponent(IRenderableTextComponent* component);
        void RegisterComponent(IDebuggable* component);

        void UnregisterComponent(IRenderableShapeComponent* component);
        void UnregisterComponent(IRenderableTextComponent* component);
        void UnregisterComponent(IDebuggable* component);

        // Application's interface to ViewStrategy
        void PollEvents();
        sf::Vector2i GetMousePosition();


        void Update(float dt);
        void SetViewStrategy(view::IViewStrategy* viewStrategy);
        
        int GetZIndexFromPool() { return m_zIndexPool++;  }
    private:
        static bool compareZIndex(const IRenderableShapeComponent* s1, const IRenderableShapeComponent* s2)
        {
            return s1->ZIndex < s2->ZIndex;
        }

        int m_zIndexPool = 1000;

        ViewSubsystem();
        
        std::unique_ptr<view::IViewStrategy> m_viewStrategy;
        std::set< IRenderableShapeComponent*, decltype(&compareZIndex)> m_shapes;
        std::vector< IRenderableTextComponent* > m_texts;
        std::vector< IDebuggable* > m_debugs;
        

    friend class SubsystemManager;
    };
};
