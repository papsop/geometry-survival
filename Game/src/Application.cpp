#include "Application.h"
#include "Singletons/SingletonManager.h"
#include "GameObject.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"

#include <iostream>
#include <type_traits>

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
        go.AddComponent<TransformComponent>(TransformComponent(go, sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f)));
        go.AddComponent<SpriteComponent>(SpriteComponent(go));

        sf::Clock clock;
        while (m_window.isOpen())
        {
            sf::Time elapsed = clock.restart();

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

            m_window.clear();

            if (!go.ShouldDestroy())
            {
                go.Update(elapsed.asSeconds());
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