#include "Application.h"
#include "Singletons/SingletonManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "Factories/GameObjectFactories.h"
#include "Components/Normal/SeekingEnemyController.h"
#include <iostream>
#include <type_traits>

namespace Game
{

    Application::Application() : m_window(sf::VideoMode(800, 600), "Dungeons & Geometry")
    {
    }

    sf::Vector2i Application::GetMousePosition()
    {
        return sf::Mouse::getPosition(m_window);
    }

    void Application::Run()
    {
        SingletonManager& singletonManager = SingletonManager::Instance();
        singletonManager.Init(*this);

        auto renderManager = SingletonManager::Instance().GetRenderManager();
        auto inputManager = SingletonManager::Instance().GetInputManager();
        // ---------------------------------------

        Scene scene;
        auto playerObj = scene.AddGameObjectViaFactory(PlayerFactory());
        auto enemy = scene.AddGameObjectViaFactory(SeekingEnemyFactory());
        if (auto tmp = enemy.lock())
            if (auto tmpII = tmp->GetComponent<SeekingEnemyController>().lock())
               tmpII->SetSeekTarget(playerObj);

        sf::Clock clock;
        while (m_window.isOpen())
        {
            sf::Time elapsed = clock.restart();

            // todo it's own handling
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
            scene.UpdateGameObjects(elapsed.asSeconds());
            scene.RenderGameObjects();
            renderManager->RenderAll();
            m_window.display();
        }
    }

    void Application::Draw(const sf::Drawable& drawable, const sf::RenderStates& states)
    {
        m_window.draw(drawable, states);
    }
};