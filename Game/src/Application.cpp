#include "Application.h"
#include "Managers/InputManager.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "View/WindowViewStrategy.h"
#include "View/ConsoleViewStrategy.h"

#include "Components/AllComponents.h"

#include "Debug/Logger.h"

#include <iostream>
#include <type_traits>
#include <memory>
#include <string>

namespace Game
{
    uint32_t IComponent::m_nextComponentID = 0;

    Application::Application()
        : m_entityManager(std::unique_ptr<EntityManager>(new EntityManager()))
        , m_subsystemManager(std::unique_ptr<SubsystemManager>(new SubsystemManager()))
        , m_inputManager(std::unique_ptr<InputManager>(new InputManager()))
    {
        // Passing unique_ptr like this, so we can keep private manager constructors
        // and link Application as friend class (won't work with make_unique)
    }

    void Application::HandleViewEvent(const sf::Event& event)
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_applicationIsRunning = false;
            break;
        default:
            m_inputManager->HandleWindowEvent(event);
            break;
        }
    }

    void Application::Run()
    {
        sf::Font font;
        if (!font.loadFromFile("arial.ttf"))
        {
            LOG_INFO("loaded font");
        }
        else LOG_WARN("Unable to load font, no clue why");

        LOG_INFO("Starting Application");
        Scene scene;
        auto debugID = scene.AddGameObjectViaFactory(DebugGOFactory());
        auto playerID = scene.AddGameObjectViaFactory(PlayerFactory());

        // Create and set ViewStrategy
        m_subsystemManager->m_view->SetViewStrategy(
            new view::WindowViewStrategy
            (
                [&](const sf::Event& event)
                {
                    this->HandleViewEvent(event);
                }
            )
        );
        // Give ViewStrategy to InputManager because of MousePosition
        m_inputManager->SetViewSubsystem(m_subsystemManager->m_view.get());

        //m_viewManager->SetViewStrategy<view::WindowViewStrategy>(
        //    [&](const sf::Event& event)
        //    {
        //        this->HandleWindowEvent(event);
        //    }
        //);

        //for (auto entity : scene.GetSceneGameObjects())
        //    std::cout << entity << std::endl;

        //scene.RemoveGameObject(1);

        //for (auto entity : scene.GetSceneGameObjects())
        //    std::cout << entity << std::endl;
        //std::cout << IComponent::GetComponentID<RigidbodyComponent>() << std::endl;
        //std::cout << IComponent::GetComponentID<ActorComponent>() << std::endl;


        sf::Clock clock;

        while (m_applicationIsRunning)
        {
            sf::Time elapsed = clock.restart();
            float lastFrameMS = elapsed.asSeconds();
            
            // Input
            //m_viewManager->PollEvents();
            m_subsystemManager->m_view->PollEvents();
            
            // debug exit
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) break;
           
//            m_window.clear();

            //for (auto entityID : scene.GetSceneGameObjects())
            //    if (auto tmp = GetEntityManager().GetEntityByID(entityID).lock())
            //        tmp->Update(lastFrameMS);
            m_inputManager->Update();
            m_subsystemManager->Update(lastFrameMS);

            //m_viewManager->PreRender();

            // TODO
            // - viewManager's cache of components to render
            // - possibility of zIndex
            // - LET'S NOT DYNAMIC CAST EVERY SINGLE COMPONENT EVERY FRAME

            //for (auto entityID : scene.GetSceneGameObjects())
            //    if (auto tmp = GetEntityManager().GetEntityByID(entityID).lock())
            //        for (auto comp : tmp->GetAllComponents())
            //        {
            //            if (auto c = std::dynamic_pointer_cast<IRenderableShape>(comp.second))
            //            {
            //                m_viewManager->Render(c->GetRenderableShape());
            //            } 
            //            else if (auto c = std::dynamic_pointer_cast<IRenderableText>(comp.second))
            //            {
            //                m_viewManager->Render(c->GetRenderableText());
            //            }
            //        }

            //m_viewManager->PostRender();

            //m_viewManager->Render();
            //sf::Text text;
            //text.setFont(font);
            //float fps = (1000 / elapsed.asSeconds());
            //std::cout << std::to_string(fps) + " fps" << std::endl;
            //std::string debugString = std::to_string(fps) + " fps";
            //text.setString(debugString);
            //text.setCharacterSize(16);
            //text.setFillColor(sf::Color::Red);
            //m_window.draw(text);

  //          m_window.display();
        }
        LOG_INFO("----------------------------- Stopping Application, time to destroy");
    }

    void Application::Draw(const sf::Drawable& drawable, const sf::RenderStates& states)
    {
        //m_window.draw(drawable, states);
    }
};