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

    sf::Vector2i ViewSubsystem::GetMousePosition()
    {
        return m_viewStrategy->GetMousePosition();
    }

    void ViewSubsystem::RegisterComponent(IRenderableShapeComponent *component)
    {
        
        if (m_shapes.insert(component).second == false)
        {
            LOG_WARN("IRenderableShape from ID: %d, zIndex '%d' already present", component->Owner.c_ID, component->ZIndex);
        }
        else
            LOG_DEBUG("registered IRenderableShape from ID: %d, zIndex: '%d'", component->Owner.c_ID, component->ZIndex);
    }

    void ViewSubsystem::RegisterComponent(IRenderableTextComponent* component)
    {
        m_texts.emplace_back(component);
        LOG_DEBUG("registered IRenderableText from ID: %d", component->Owner.c_ID);
    }

    void ViewSubsystem::RegisterComponent(IDebuggable* component)
    {
        m_debugs.emplace_back(component);
        LOG_DEBUG("registered IDebugDrawComponent from ID");
    }

    void ViewSubsystem::UnregisterComponent(IRenderableShapeComponent* component)
    {
        m_shapes.erase(component);
        LOG_DEBUG("unregistered IRenderableShape from ID: %d", component->Owner.c_ID);
    }

    void ViewSubsystem::UnregisterComponent(IRenderableTextComponent* component)
    {
        m_texts.erase(std::remove(m_texts.begin(), m_texts.end(), component), m_texts.end());
        LOG_DEBUG("unregistered IRenderableText from ID: %d", component->Owner.c_ID);
    }

    void ViewSubsystem::UnregisterComponent(IDebuggable* component)
    {
        m_debugs.erase(std::remove(m_debugs.begin(), m_debugs.end(), component), m_debugs.end());
        LOG_DEBUG("unregistered IDebugDrawComponent");
    }

    void ViewSubsystem::Update(float dt)
    {
        m_viewStrategy->PreRender();

        for (auto r : m_shapes)
            if (r->Owner.ShouldUpdate())
                m_viewStrategy->Render(r->GetRenderableShape());
                

        for (auto t : m_texts)
            if (t->Owner.ShouldUpdate())
                m_viewStrategy->Render(t->GetRenderableText());

        // debug draws for registered components
        for (auto d : m_debugs)
                d->Debug(m_viewStrategy.get());

        m_viewStrategy->PostRender();
    }
};