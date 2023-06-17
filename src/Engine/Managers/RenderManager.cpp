#include "RenderManager.h"
#include "../Application.h"

#include "../ImGui/imgui.h"
#include "../ImGui/imgui-SFML.h"

namespace Engine
{

	RenderManager::RenderManager()
		: m_debugContext(*this)
	{
		m_resolutionEntries.push_back({"1280x720", {1280, 720} });
		m_resolutionEntries.push_back({"1920x1024", {1920, 1024} });

		m_currentSettings.Fullscreen = false;
		m_currentSettings.ResolutionEntry = m_resolutionEntries[0];
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
		EnsureLocked();
		m_drawableComponents.push_back(component);
	}

	void RenderManager::RegisterComponent(IDebuggable* component)
	{
		EnsureLocked();
		m_debuggableComponents.push_back(component);
	}

	void RenderManager::RegisterComponent(IImGuiComponent* component)
	{
		EnsureLocked();
		m_imGuiComponents.push_back(component);
	}

	void RenderManager::UnregisterComponent(IDrawableComponent* component)
	{
		EnsureLocked();
		m_drawableComponents.erase(std::remove(m_drawableComponents.begin(), m_drawableComponents.end(), component), m_drawableComponents.end());
	}

	void RenderManager::UnregisterComponent(IDebuggable* component)
	{
		EnsureLocked();
		m_debuggableComponents.erase(std::remove(m_debuggableComponents.begin(), m_debuggableComponents.end(), component), m_debuggableComponents.end());
	}

	void RenderManager::UnregisterComponent(IImGuiComponent* component)
	{
		EnsureLocked();
		m_imGuiComponents.erase(std::remove(m_imGuiComponents.begin(), m_imGuiComponents.end(), component), m_imGuiComponents.end());
	}

	void RenderManager::SetView(CameraData cameraData)
	{
		sf::View view;
		view.setCenter(coordsPosToPixelsPos(cameraData.Center));
		view.setSize(1280, 720);
		view.setViewport({ .0f, .0f, 1.f, 1.f });
		m_window->setView(view);
	}

	void RenderManager::SetSettings(RenderManagerSettings settings)
	{
		m_currentSettings = settings;
		this->OnSettingsChanged.Invoke();

		Application::Instance().AddEndOfFrameDeferredAction(
			[&]() {
				ReloadWindow();
			}
		);
	}

	void RenderManager::ReceiveEvent(const event::E_OnShowDebugKeyAction& eventData)
	{
		m_shouldUpdateDebugs = !m_shouldUpdateDebugs;
	}

	void RenderManager::ReloadWindow()
	{
		if (m_window)
			ImGui::SFML::Shutdown(); // before we destroy the old window

		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;
		sf::VideoMode videoMode(m_currentSettings.ResolutionEntry.Value.x, m_currentSettings.ResolutionEntry.Value.y, 32);
		uint32 style = sf::Style::Titlebar | sf::Style::Close;
		if (m_currentSettings.Fullscreen)
			style = sf::Style::Fullscreen;

		m_window = std::make_unique<sf::RenderWindow>(videoMode, "test", style, settings);
		m_window->setJoystickThreshold(10);
		m_debugContext.SetRenderWindow(m_window.get());

		ImGui::SFML::Init(*m_window);
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;// | ImGuiConfigFlags_ViewportsEnable;
	}

	void RenderManager::DestroyWindow()
	{
		if (!m_window)
			return;

		ImGui::SFML::Shutdown();
		m_window = nullptr;
		Engine::EventManager::Get().DispatchEvent(event::E_WindowClosed());
	}

	void RenderManager::RenderDebugDraw(float dt)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 work_size = viewport->WorkSize;
		ImGui::SetNextWindowPos(ImVec2(work_size.x, work_size.y), ImGuiCond_Always, ImVec2(1.0f, 1.0f));
		ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;

		if (ImGui::Begin("ViewManager", NULL, window_flags))
		{
			ImGui::Text("Frame time: %.5f", dt);
			ImGui::Text("FPS: %.1f\n", (1.f / dt));
		}
		ImGui::End();
	}

	void RenderManager::Update(float dt)
	{
		if (!m_window)
			return;
		Lock();
		// Just an update of components, not rendering yet
		for (auto& c : m_drawableComponents)
		{
			if (c->ShouldUpdate())
			{
				c->Update(dt);
			}
		}

		m_window->clear();

		RenderDrawables(dt);
		RenderImGui(dt);

		m_window->display();
		Unlock();
	}

	void RenderManager::RenderDrawables(float dt)
	{
		IDrawableComponent::TDrawablesMap m_layersDrawableData;
		// get all the drawables
		for (auto& drawableComponent : m_drawableComponents)
		{
			drawableComponent->GetDrawables(m_layersDrawableData);
		}

		// draw them
		for (auto& layer : m_layersDrawableData)
		{
			for (auto& drawableData : layer)
			{
				if (drawableData.Shader)
				{
					m_window->draw(*drawableData.Drawable, drawableData.Shader);
				}
				else
				{
					m_window->draw(*drawableData.Drawable);
				}
			}
		}
	}

	void RenderManager::RenderImGui(float dt)
	{
		ImGui::SFML::Update(*m_window, sf::seconds(dt));
		ImGui::SFML::SetCurrentWindow(*m_window);

		for (auto& c : m_imGuiComponents)
		{
			if (c->ShouldUpdate())
			{
				c->Update(dt);
			}
		}

		if (m_shouldUpdateDebugs)
		{
			for (auto& c : m_debuggableComponents)
			{
				c->Debug(m_debugContext);
			}
			RenderDebugDraw(dt);
		}

		ImGui::SFML::Render(*m_window);
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
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