#include "GameObject.h"
#include "Components/RenderComponent.h"

namespace Game
{
    void GameObject::Update(float dt)
    {
        for (auto component : m_components)
            component.second->Update(dt);
    }

    void GameObject::Render()
    {
        if(HasComponent<RenderComponent>())
            GetComponent<RenderComponent>()->Render();
    }
};