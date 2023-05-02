#include "ViewManager.h"

#include "../Application.h"
#include "../Core/GameObject/GameObject.h"
#include "../Debug/Logger.h"

#include "../Managers/ViewManager.h"
#include "../Managers/ConfigManager.h"
#include "../Managers/InputManager.h"
#include "../Managers/UIManager.h"

#include "../ImGui/imgui.h"
namespace Engine
{
	ViewManager::ViewManager()
		: m_renderableComponents()
		, m_viewStrategy()
	{
	}

	ViewManager& ViewManager::Get()
	{
		return Application::Instance().GetViewManager();
	}

	void ViewManager::VirtualOnInit()
	{
		ConfigManager::Get().RegisterCvar("view_pixelsPerMeter", &m_pixelsPerMeter, 10);

		IEventListener<event::E_OnShowDebugKeyAction>::RegisterListener();
	}

	void ViewManager::VirtualOnDestroy()
	{
		m_viewStrategy = nullptr;

		IEventListener<event::E_OnShowDebugKeyAction>::UnregisterListener();
	}


	void ViewManager::ReceiveEvent(const event::E_OnShowDebugKeyAction& eventData)
  {
    m_shouldDrawDebug = !m_shouldDrawDebug;
  }

  void ViewManager::SetViewStrategy(view::IViewStrategy* viewStrategy)
	{
		m_viewStrategy.reset(viewStrategy);
	}

	void ViewManager::PollEvents()
	{
		m_viewStrategy->PollEvents();
	}

	sf::Vector2f ViewManager::GetMousePosition()
	{
		return m_viewStrategy->GetMousePosition();
	}

	sf::Vector2f ViewManager::coordsToPixels(b2Vec2 coords)
	{
		return { coords.x * m_pixelsPerMeter, -coords.y * m_pixelsPerMeter };
	}

	b2Vec2 ViewManager::pixelsToCoords(sf::Vector2f pixels)
	{
		return { pixels.x / m_pixelsPerMeter, -pixels.y / m_pixelsPerMeter };
	}

	float ViewManager::coordToPixel(float coord)
	{
		return coord * m_pixelsPerMeter;
	}

	float ViewManager::pixelToCoord(float pixel)
	{
		return pixel / m_pixelsPerMeter;
	}

  sf::Vector2i ViewManager::MapCoordsToPixel(sf::Vector2f coords)
  {
		return m_viewStrategy->MapCoordsToPixel(coords);
  }

  sf::Vector2f ViewManager::MapPixelToCoords(sf::Vector2i pixel)
  {
		return m_viewStrategy->MapPixelToCoords(pixel);
  }

  // ==================================================================

	void ViewManager::RegisterComponent(IRenderableComponent* component)
	{
		m_renderableComponents.insert({ component->GetLayer(), component });
	}

	void ViewManager::RegisterComponent(IDebuggable* component)
	{
		m_debugs.emplace_back(component);
	}

//   void ViewManager::RegisterComponent(IUIComponent* component)
//   {
//     //m_uiComponents.emplace_back(component);
//   }

	void ViewManager::RegisterComponent(IImGuiComponent* component)
	{
		m_imguiComponents.emplace_back(component);
	}

	void ViewManager::RegisterComponent(IDrawableComponent* component)
	{
		m_drawableComponents.emplace_back(component);
	}

	// ==================================================================

	void ViewManager::UnregisterComponent(IRenderableComponent* component)
	{
		for (auto iter = m_renderableComponents.begin(); iter != m_renderableComponents.end(); /* */ )
		{
			auto erase_iter = iter++;

			if (erase_iter->second == component)
				m_renderableComponents.erase(erase_iter);
		}
	}

//   void ViewManager::UnregisterComponent(IUIComponent* component)
//   {
//     //m_uiComponents.erase(std::remove(m_uiComponents.begin(), m_uiComponents.end(), component), m_uiComponents.end());
//   }

	void ViewManager::UnregisterComponent(IImGuiComponent* component)
	{
		m_imguiComponents.erase(std::remove(m_imguiComponents.begin(), m_imguiComponents.end(), component), m_imguiComponents.end());
	}

	void ViewManager::UnregisterComponent(IDebuggable* component)
	{
		m_debugs.erase(std::remove(m_debugs.begin(), m_debugs.end(), component), m_debugs.end());
	}

	void ViewManager::UnregisterComponent(IDrawableComponent* component)
	{
		m_drawableComponents.erase(std::remove(m_drawableComponents.begin(), m_drawableComponents.end(), component), m_drawableComponents.end());
	}

	// ==================================================================
	void ViewManager::DebugDraw(float dt)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 work_size = viewport->WorkSize;
		ImGui::SetNextWindowPos(ImVec2(work_size.x, work_size.y), ImGuiCond_Always, ImVec2(1.0f, 1.0f));
		ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;

		if (ImGui::Begin("ViewManager", NULL, window_flags))
		{
			ImGui::Text("Frame time: %.5f", dt);
			ImGui::Text("FPS: %.1f\n", (1000.0f/dt));
		}
		ImGui::End();
	}

	void ViewManager::Update(float dt)
	{
		if (m_isViewdirty)
		{
			m_viewStrategy->ReloadView();
			m_isViewdirty = false;
		}

		m_viewStrategy->Update(dt);

		m_viewStrategy->PreRender();

		// UI
    for (auto& c : m_imguiComponents)
    {
			if (c->ShouldUpdate())
			{
				c->Update(dt);
			}
    }

		// VIEW
		for (auto& r : m_renderableComponents)
		{
			auto component = r.second;
			if (component->ShouldUpdate())
			{
				component->Update(dt);
				m_viewStrategy->RenderRenderable(component->GetRenderable());
			}
		}

		// debug draws for registered components
		if (m_shouldDrawDebug)
		{
			for (auto& d : m_debugs)
				d->Debug(m_viewStrategy.get());

			DebugDraw(dt); // my own
		}

		// draw UI
		//UIManager::Get().DrawGui();

		m_viewStrategy->PostRender();
	}
};