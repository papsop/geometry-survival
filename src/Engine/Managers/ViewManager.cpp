#include "ViewManager.h"

#include "../Application.h"
#include "../Core/GameObject.h"
#include "../Debug/Logger.h"

namespace Engine
{
	ViewManager::ViewManager()
		: m_shapes(&compareZIndex)
		, m_texts()
		, m_viewStrategy()
	{
	}

	ViewManager& ViewManager::Get()
	{
		return Application::Instance().GetViewManager();
	}

	void ViewManager::OnInit()
	{	
		IManager::OnInit();
	}

	void ViewManager::OnDestroy()
	{
		Logger::Instance().ClearBackends();
		m_viewStrategy = nullptr;
		IManager::OnDestroy();
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
		return { coords.x * PIXELS_PER_METER, -coords.y * PIXELS_PER_METER };
	}

	b2Vec2 ViewManager::pixelsToCoords(sf::Vector2f pixels)
	{
		return { pixels.x / PIXELS_PER_METER, -pixels.y / PIXELS_PER_METER };
	}

	float ViewManager::coordToPixel(float coord)
	{
		return coord * PIXELS_PER_METER;
	}

	float ViewManager::pixelToCoord(float pixel)
	{
		return pixel / PIXELS_PER_METER;
	}

	// ==================================================================

	void ViewManager::RegisterComponent(IRenderableShapeComponent* component)
	{

		if (m_shapes.insert(component).second == false)
		{
			LOG_WARN("IRenderableShape from ID: %d, zIndex '%d' already present", component->Owner.c_ID, component->ZIndex);
		}
	}

	void ViewManager::RegisterComponent(IRenderableTextComponent* component)
	{
		m_texts.emplace_back(component);
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

	void ViewManager::UnregisterComponent(IRenderableShapeComponent* component)
	{
		m_shapes.erase(component);
	}

	void ViewManager::UnregisterComponent(IRenderableTextComponent* component)
	{
		m_texts.erase(std::remove(m_texts.begin(), m_texts.end(), component), m_texts.end());
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

		for (auto c : m_cameras)
			if (c->Owner.ShouldUpdate())
				c->Update(dt);

		for (auto r : m_shapes)
			if (r->Owner.ShouldUpdate())
			{
				r->Update(dt);
				m_viewStrategy->RenderRenderable(r->GetRenderable());
			}

		for (auto t : m_texts)
			if (t->Owner.ShouldUpdate())
				m_viewStrategy->Render(t->GetRenderableText());

		// debug draws for registered components
		if (m_shouldDrawDebug)
		{
			for (auto d : m_debugs)
				d->Debug(m_viewStrategy.get());
		}

		m_viewStrategy->PostRender();
	}
};