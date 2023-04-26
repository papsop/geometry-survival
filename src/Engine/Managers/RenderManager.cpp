#include "RenderManager.h"
#include "../Application.h"

#include "../ImGui/imgui.h"
#include "../ImGui/imgui-SFML.h"

namespace Engine
{

	RenderManager::RenderManager()
		: m_debugContext(*this)
	{

	}

	RenderManager& RenderManager::Get()
	{
		return Application::Instance().GetRenderManager();
	}

	void RenderManager::VirtualOnInit()
	{
		IEventListener<event::E_OnShowDebugKeyAction>::RegisterListener();
		ReloadWindow();

		// todo resource manager?
		if (!m_font.loadFromFile("assets/arial.ttf"))
		{
			LOG_ERROR("Unable to load console font");
		}
	}

	void RenderManager::VirtualOnDestroy()
	{
		IEventListener<event::E_OnShowDebugKeyAction>::UnregisterListener();
		ImGui::SFML::Shutdown();
	}

	void RenderManager::RegisterComponent(IDrawableComponent* component)
	{
		m_drawableComponents.push_back(component);
	}

  void RenderManager::RegisterComponent(IDebuggable* component)
  {
		m_debuggableComponents.push_back(component);
  }

	void RenderManager::RegisterComponent(IImGuiComponent* component)
	{
		m_imGuiComponents.push_back(component);
	}

	void RenderManager::UnregisterComponent(IDrawableComponent* component)
	{
		m_drawableComponents.erase(std::remove(m_drawableComponents.begin(), m_drawableComponents.end(), component), m_drawableComponents.end());
	}

  void RenderManager::UnregisterComponent(IDebuggable* component)
  {
		m_debuggableComponents.erase(std::remove(m_debuggableComponents.begin(), m_debuggableComponents.end(), component), m_debuggableComponents.end());
  }

	void RenderManager::UnregisterComponent(IImGuiComponent* component)
	{
		m_imGuiComponents.erase(std::remove(m_imGuiComponents.begin(), m_imGuiComponents.end(), component), m_imGuiComponents.end());
	}

	void RenderManager::SetView(CameraData cameraData)
	{
		sf::View view;
		view.setCenter(coordsToPixels(cameraData.Center));
		view.setSize(1280, 720);
		view.setViewport({ .0f, .0f, 1.f, 1.f });
		m_window->setView(view);
	}

	void RenderManager::ReceiveEvent(const event::E_OnShowDebugKeyAction& eventData)
	{
		m_shouldUpdateDebugs = !m_shouldUpdateDebugs;
	}

	void RenderManager::ReloadWindow()
	{
		ImGui::SFML::Shutdown(); // before we destroy the old window

		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;
		sf::VideoMode videoMode(1280, 720, 32);
		uint32 style = sf::Style::Titlebar | sf::Style::Close;

		m_window = std::make_unique<sf::RenderWindow>(videoMode, "test", style, settings);
		m_window->setJoystickThreshold(10);
		m_debugContext.SetRenderWindow(m_window.get());

		ImGui::SFML::Init(*m_window);
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	}

  void RenderManager::DestroyWindow()
  {
		if (!m_window)
			return;

		ImGui::SFML::Shutdown();
		m_window = nullptr;
		Engine::EventManager::Get().DispatchEvent(event::E_WindowClosed());
  }

  void RenderManager::ApplyTransformToDrawable(const ITransform::AbsoluteTransform transform, sf::Drawable* drawable)
	{
		auto* transformableObject = dynamic_cast<sf::Transformable*>(drawable);
		if (!transformableObject)
			return;

		transformableObject->setPosition(coordsToPixels(transform.Position));
		transformableObject->setRotation(Box2DRotationToSFML(transform.Rotation));
		transformableObject->setScale({ 1.0f, 1.0f });
	}

	void RenderManager::Update(float dt)
	{
		if (m_window)
			ImGui::SFML::Update(*m_window, sf::seconds(dt));

		for (auto& c : m_drawableComponents)
		{
			if (c->ShouldUpdate())
			{
				c->Update(dt);
			}
		}

		for (auto& c : m_imGuiComponents)
		{
			if (c->ShouldUpdate())
			{
				c->Update(dt);
			}
		}

		Render(dt);
	}

	void RenderManager::Render(float dt)
	{
		if (!m_window)
			return;

		IDrawableComponent::TDrawablesMap drawables;
		
		m_window->clear();

		// get all the drawables
		for (auto& drawableComponent : m_drawableComponents)
		{
			drawableComponent->GetDrawables(drawables);
		}


		// draw them
		for (auto& [layer, data] : drawables)
		{
			ApplyTransformToDrawable(data.first, data.second);

			m_window->draw(*data.second);
		}
		
		// debuggable

    for (auto& c : m_debuggableComponents)
    {
      c->Debug(m_debugContext);
    }

		ImGui::SFML::Render(*m_window);
		m_window->display();
	}

	void RenderManager::PollEvents()
	{
		if (!m_window)
			return;

		sf::Event event;
		while (m_window->pollEvent(event))
		{
			if (m_window)
				ImGui::SFML::ProcessEvent(event);
			Engine::EventManager::Get().DispatchEvent(event::E_SFMLEvent(event));
		}
	}

	sf::Vector2f RenderManager::GetMousePosition()
	{
		if (!m_window)
			return {};

		auto pos = sf::Mouse::getPosition(*m_window);
		return m_window->mapPixelToCoords(pos);
	}

}