#pragma once
#include "../Components/View.h"
#include "../View/IViewStrategy.h"

#include <vector>
#include <set>
#include <memory>

namespace Game
{
    class SubsystemManager;

    class ViewSubsystem
    {
    public:
        ~ViewSubsystem();

        void RegisterComponent(IComponent* component);
        void UnregisterComponent(IComponent* component);

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
        

    friend class SubsystemManager;
    };
};
