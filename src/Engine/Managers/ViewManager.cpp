#include "ViewManager.h"

#include "../Application.h"
#include "../Core/GameObject/GameObject.h"
#include "../Debug/Logger.h"

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
		ConfigManager::Get().RegisterCvar("view_pixelsPerMeter", &m_pixelsPerMeter, 15);
	}

	void ViewManager::VirtualOnDestroy()
	{
		m_viewStrategy = nullptr;
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

	// ==================================================================

	void ViewManager::RegisterComponent(IRenderableComponent* component)
	{
		m_renderableComponents.insert({ component->GetLayer(), component });
	}

	void ViewManager::RegisterComponent(IDebuggable* component)
	{
		m_debugs.emplace_back(component);
	}

	void ViewManager::RegisterComponent(CameraComponent* component)
	{
		m_cameras.emplace_back(component);
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

	void ViewManager::UnregisterComponent(IDebuggable* component)
	{
		m_debugs.erase(std::remove(m_debugs.begin(), m_debugs.end(), component), m_debugs.end());
	}

	void ViewManager::UnregisterComponent(CameraComponent* component)
	{
		m_cameras.erase(std::remove(m_cameras.begin(), m_cameras.end(), component), m_cameras.end());
	}

	// ==================================================================

	void ViewManager::Update(float dt)
	{
		if (InputManager::Get().GetAction(InputManager::Action::ShowDebugDraw).PressedThisFrame)
			m_shouldDrawDebug = !m_shouldDrawDebug;

		m_viewStrategy->PreRender();

		for (auto& c : m_cameras)
			if (c->Owner.ShouldUpdate())
				c->Update(dt);

		for (auto& r : m_renderableComponents)
		{
			auto component = r.second;
			if (component->Owner.ShouldUpdate())
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
		}

		m_viewStrategy->PostRender();
	}
};