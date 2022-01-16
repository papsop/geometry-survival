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
        LOG_INFO("Created ViewSubsystem");
    }

    ViewSubsystem::~ViewSubsystem()
    {
        LOG_INFO("Destroyed ViewSubsystem");
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
            LOG_WARN("IRenderableShape from ID: %d, zIndex '%d' already present", component->Owner.ID, component->ZIndex);
        }
        else
            LOG_INFO("registered IRenderableShape from ID: %d, zIndex: '%d'", component->Owner.ID, component->ZIndex);
    }

    void ViewSubsystem::RegisterComponent(IRenderableTextComponent* component)
    {
        m_texts.emplace_back(component);
        LOG_INFO("registered IRenderableText from ID: %d", component->Owner.ID);
    }

    void ViewSubsystem::RegisterComponent(IDebugDrawComponent* component)
    {
        m_debugs.emplace_back(component);
        LOG_INFO("registered IDebugDrawComponent from ID");
    }

    void ViewSubsystem::UnregisterComponent(IRenderableShapeComponent* component)
    {
        m_shapes.erase(component);
        LOG_INFO("unregistered IRenderableShape from ID: %d", component->Owner.ID);
    }

    void ViewSubsystem::UnregisterComponent(IRenderableTextComponent* component)
    {
        m_texts.erase(std::remove(m_texts.begin(), m_texts.end(), component), m_texts.end());
        LOG_INFO("unregistered IRenderableText from ID: %d", component->Owner.ID);
    }

    void ViewSubsystem::UnregisterComponent(IDebugDrawComponent* component)
    {
        m_debugs.erase(std::remove(m_debugs.begin(), m_debugs.end(), component), m_debugs.end());
        LOG_INFO("unregistered IDebugDrawComponent");
    }

    void ViewSubsystem::Update(float dt)
    {
        m_viewStrategy->PreRender();

        for (auto r : m_shapes)
            m_viewStrategy->Render(r->GetRenderableShape());

        for (auto t : m_texts)
            m_viewStrategy->Render(t->GetRenderableText());

        // debug draws for registered components
        for (auto d : m_debugs)
            d->DebugDraw(m_viewStrategy.get());

        m_viewStrategy->PostRender();
    }
};