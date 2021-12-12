#include "Application.h"
#include "Singletons/InputManager.h"
#include "Singletons/RenderManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "Factories/GameObjectFactories.h"
#include "Components/Normal/SeekingEnemyController.h"
#include <iostream>
#include <type_traits>
#include <memory>
#include <string>

namespace Game
{
    uint32_t IComponent::m_nextComponentID = 0;

    Application::Application()
        : m_window(sf::VideoMode(1024, 768), "Dungeons & Geometry")
        , m_inputManager(std::unique_ptr<InputManager>(new InputManager(*this)))
        , m_renderManager(std::unique_ptr<RenderManager>(new RenderManager(*this)))
        , m_entityManager(std::unique_ptr<EntityManager>(new EntityManager()))
    {
        // Passing unique_ptr like this, so we can keep private manager constructors
        // and link Application as friend class (won't work with make_unique)
    }

    sf::Vector2i Application::GetMousePosition()
    {
        return sf::Mouse::getPosition(*m_window);
    }

    void Application::Run()
    {
        auto renderManager = GetRenderManager();
        auto inputManager = GetInputManager();
        // ---------------------------------------

        Scene scene;
        auto playerID = scene.AddGameObjectViaFactory(PlayerFactory());

        //for (auto entity : scene.GetSceneGameObjects())
        //    std::cout << entity << std::endl;

        //scene.RemoveGameObject(1);

        //for (auto entity : scene.GetSceneGameObjects())
        //    std::cout << entity << std::endl;
        //std::cout << IComponent::GetComponentID<RigidbodyComponent>() << std::endl;
        //std::cout << IComponent::GetComponentID<ActorComponent>() << std::endl;


        sf::Clock clock;

        sf::Font font;
        if (!font.loadFromFile("arial.ttf"))
        {
            return;
        }

        while (m_window.isOpen())
        {
            sf::Time elapsed = clock.restart();

            // todo it's own handling
            sf::Event event;
            while (m_window->pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    m_window->close();
                    break;
                case sf::Event::KeyPressed:
                    inputManager.KeyPressed(event.key.code);
                    break;
                case sf::Event::KeyReleased:
                    inputManager.KeyReleased(event.key.code);
                    break;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                m_window.close();

            m_window.clear();


            for (auto entityID : scene.GetSceneGameObjects())
                if (auto tmp = GetEntityManager().GetEntityByID(entityID).lock())
                    tmp->Update(elapsed.asSeconds());

            sf::Text text;
            text.setFont(font);
            float fps = (1000 / elapsed.asSeconds());
            std::string debugString = std::to_string(fps) + " fps";
            text.setString(debugString);
            text.setCharacterSize(16);
            text.setFillColor(sf::Color::Red);
            m_window.draw(text);

            m_window.display();
        }
    }

    void Application::Draw(const sf::Drawable& drawable, const sf::RenderStates& states)
    {
        m_window->draw(drawable, states);
    }
};