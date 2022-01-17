#pragma once
#include "../Components/View.h"
#include "../View/IViewStrategy.h"

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
        void RegisterComponent(IDebugDrawComponent* component);

        void UnregisterComponent(IRenderableShapeComponent* component);
        void UnregisterComponent(IRenderableTextComponent* component);
        void UnregisterComponent(IDebugDrawComponent* component);

        // Application's interface to ViewStrategy
        void PollEvents();
        sf::Vector2i GetMousePosition();


        void Update(float dt);
        void SetViewStrategy(view::IViewStrategy* viewStrategy);
        
    private:
        static bool compareZIndex(const IRenderableShapeComponent* s1, const IRenderableShapeComponent* s2)
        {
            return s1->ZIndex < s2->ZIndex;
        }

        ViewSubsystem();
        
        std::unique_ptr<view::IViewStrategy> m_viewStrategy;
        std::set< IRenderableShapeComponent*, decltype(&compareZIndex)> m_shapes;
        std::vector< IRenderableTextComponent* > m_texts;
        std::vector< IDebugDrawComponent* > m_debugs;

    friend class SubsystemManager;
    };
};
