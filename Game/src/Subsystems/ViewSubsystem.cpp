#include "ViewSubsystem.h"

#include "../Core/GameObject.h"
#include "../Debug/Logger.h"

namespace Game
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

    void ViewSubsystem::RegisterComponent(IComponent *component)
    {
        if (auto shapeComponent = dynamic_cast<IRenderableShapeComponent*>(component))
        {
            m_shapes.insert(shapeComponent);
            LOG_INFO("{ViewSubsystem} registered IRenderableShape from ID: %d", shapeComponent->Owner.ID);
        }
        else if (auto textComponent = dynamic_cast<IRenderableTextComponent*>(component))
        {
            m_texts.emplace_back(textComponent);
            LOG_INFO("{ViewSubsystem} registered IRenderableText from ID: %d", textComponent->Owner.ID);
        }
    }

    void ViewSubsystem::UnregisterComponent(IComponent* component)
    {
        if (auto shapeComponent = dynamic_cast<IRenderableShapeComponent*>(component))
        {
            m_shapes.erase(shapeComponent);
            LOG_INFO("{ViewSubsystem} unregistered IRenderableShape from ID: %d", shapeComponent->Owner.ID);
        }
        else if (auto textComponent = dynamic_cast<IRenderableTextComponent*>(component))
        {
            m_texts.erase(std::remove(m_texts.begin(), m_texts.end(), textComponent), m_texts.end());
            LOG_INFO("{ViewSubsystem} unregistered IRenderableText from ID: %d", textComponent->Owner.ID);
        }
    }

    void ViewSubsystem::Update(float dt)
    {
        m_viewStrategy->PreRender();

        for (auto r : m_shapes)
            m_viewStrategy->Render(r->GetRenderableShape());

        for (auto t : m_texts)
            m_viewStrategy->Render(t->GetRenderableText());

        m_viewStrategy->PostRender();
    }
};