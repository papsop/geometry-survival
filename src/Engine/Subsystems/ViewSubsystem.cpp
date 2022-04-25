#include "ViewSubsystem.h"

#include "../Application.h"
#include "../Core/GameObject.h"
#include "../Debug/Logger.h"

namespace Engine
{
    ViewSubsystem::ViewSubsystem()
        : m_shapes(&compareZIndex)
        , m_texts()
        , m_viewStrategy()
    {
        LOG_DEBUG("Created ViewSubsystem");
    }

	ViewSubsystem::~ViewSubsystem()
    {
        LOG_DEBUG("Destroyed ViewSubsystem");
    }

    void ViewSubsystem::SetViewStrategy(view::IViewStrategy* viewStrategy)
    {
        m_viewStrategy.reset(viewStrategy);
    }

    void ViewSubsystem::PollEvents()
    {
        m_viewStrategy->PollEvents();
    }

    sf::Vector2f ViewSubsystem::GetMousePosition()
    {
        return m_viewStrategy->GetMousePosition();
	}

	sf::Vector2f ViewSubsystem::coordsToPixels(b2Vec2 coords)
	{
		return { coords.x * PIXELS_PER_METER, -coords.y * PIXELS_PER_METER };
	}

	b2Vec2 ViewSubsystem::pixelsToCoords(sf::Vector2f pixels)
	{
		return { pixels.x / PIXELS_PER_METER, -pixels.y / PIXELS_PER_METER };
	}

	float ViewSubsystem::coordToPixel(float coord)
	{
        return coord * PIXELS_PER_METER;
	}

	float ViewSubsystem::pixelToCoord(float pixel)
	{
        return pixel / PIXELS_PER_METER;
	}

	// ==================================================================

    void ViewSubsystem::RegisterComponent(IRenderableShapeComponent *component)
    {
        
        if (m_shapes.insert(component).second == false)
        {
            LOG_WARN("IRenderableShape from ID: %d, zIndex '%d' already present", component->Owner.c_ID, component->ZIndex);
        }
    }

    void ViewSubsystem::RegisterComponent(IRenderableTextComponent* component)
    {
        m_texts.emplace_back(component);
    }

    void ViewSubsystem::RegisterComponent(IDebuggable* component)
    {
        m_debugs.emplace_back(component);
    }

	void ViewSubsystem::RegisterComponent(CameraComponent* component)
	{
		m_cameras.emplace_back(component);
	}

    // ==================================================================

    void ViewSubsystem::UnregisterComponent(IRenderableShapeComponent* component)
    {
        m_shapes.erase(component);
    }

    void ViewSubsystem::UnregisterComponent(IRenderableTextComponent* component)
    {
        m_texts.erase(std::remove(m_texts.begin(), m_texts.end(), component), m_texts.end());
    }

    void ViewSubsystem::UnregisterComponent(IDebuggable* component)
    {
        m_debugs.erase(std::remove(m_debugs.begin(), m_debugs.end(), component), m_debugs.end());
    }

	void ViewSubsystem::UnregisterComponent(CameraComponent* component)
	{
        m_cameras.erase(std::remove(m_cameras.begin(), m_cameras.end(), component), m_cameras.end());
	}

    // ==================================================================

    void ViewSubsystem::Update(float dt)
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