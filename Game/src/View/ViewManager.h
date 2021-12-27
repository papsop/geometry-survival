#pragma once
#include "IViewStrategy.h"
#include "../Components/Core.h"
#include <SFML/Window.hpp>
#include <functional>
#include <memory>

namespace Game
{
    class Application;

    namespace view
    {
        class ViewManager
        {
        public:
            ~ViewManager() = default;

            void PollEvents();

            template <typename T>
            void SetViewStrategy(std::function<void(const sf::Event &event)> handleEvent)
            {
                m_viewStrategy = std::make_unique<T>(handleEvent);
            }

            void RegisterComponent(IComponent *component);

            void PreRender();

            template<typename... Args>
            void Render(Args&& ...args)
            {
                m_viewStrategy->Render(std::forward<Args>(args) ...);
            }

            void PostRender();

            void RenderRegisteredComponents();

        private:
            ViewManager() = default;

            std::unique_ptr<IViewStrategy> m_viewStrategy;
            std::vector<Shape*> m_shapes = {};

        friend class Application;
        };
    };
    
};


