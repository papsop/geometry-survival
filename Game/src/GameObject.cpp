#include "GameObject.h"
#include <iostream>
namespace Game
{
    void GameObject::Update(float dt)
    {
        for (auto component : m_components)
            component.second->Update(dt);
    }

    void GameObject::Render()
    {
        for (auto renderableComponent : m_renderableComponents)
            renderableComponent.second->Render();
    }
};