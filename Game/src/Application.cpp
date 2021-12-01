#include "Application.h"
#include "Singletons/SingletonManager.h"
#include "GameObject.h"
#include "Components/TransformComponent.h"
#include "Components/RenderComponent.h"

#include <iostream>

namespace Game
{
    void Application::Run()
    {
        SingletonManager& singletonManager = SingletonManager::Instance();
        singletonManager.Init(*this);

        auto renderManager = SingletonManager::Instance().GetRenderManager();
        auto inputManager = SingletonManager::Instance().GetInputManager();
        // ---------------------------------------


        GameObject go;
        go.AddComponent<TransformComponent>(TransformComponent(sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f)));

        while (m_window.isOpen())
        {
            sf::Event event;
            while (m_window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                case sf::Event::KeyPressed:
                    inputManager->KeyPressed(event.key.code);
                    break;
                case sf::Event::KeyReleased:
                    inputManager->KeyReleased(event.key.code);
                    break;
                }
            }

            if (inputManager->IsKeyPressed(sf::Keyboard::Key::Escape))
                m_window.close();

            if (inputManager->IsKeyPressed(sf::Keyboard::Key::E))
                go.RemoveComponent<RenderComponent>();
            if (inputManager->IsKeyPressed(sf::Keyboard::Key::A))
                go.AddComponent<RenderComponent>(RenderComponent());

            m_window.clear();

            if (!go.ShouldDestroy())
            {
                go.Update(0.0f);
                if (go.IsRenderable())
                    go.Render();
            }

            m_window.display();
        }
    }

    void Application::Draw(const sf::Drawable& drawable, const sf::RenderStates& states)
    {
        m_window.draw(drawable, states);
    }
};