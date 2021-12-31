#include "FpsCounterComponent.h"

#include "../../Core/GameObject.h"
#include "../../Application.h"

namespace Game
{
    FpsCounterComponent::FpsCounterComponent(GameObject& obj)
        : IRenderableTextComponent(obj)
        , m_text(obj.GetTransform())
    {
        VIEWSUBSYSTEM_REGISTER(this);
    }

    FpsCounterComponent::~FpsCounterComponent()
    {
        VIEWSUBSYSTEM_UNREGISTER(this);
    }
    
    void FpsCounterComponent::Update(float dt)
    {
        m_text.Value = "Test";
    }

    const view::Text& FpsCounterComponent::GetRenderableText()
    {
        return m_text;
    }
};