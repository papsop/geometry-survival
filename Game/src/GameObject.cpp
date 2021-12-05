#include "GameObject.h"
#include <iostream>
namespace Game
{

    void GameObject::InitAllComponents()
    {
        for (auto component : m_components)
            component.second->Init();

        for (auto component : m_renderableComponents)
            component.second->Init();
    }

    void GameObject::Update(float dt)
    {
        if (m_transform.Rotation > 360.0f || m_transform.Rotation < -360.0f)
            m_transform.Rotation = fmod(m_transform.Rotation, 360);

        for (auto component : m_components)
            component.second->Update(dt);
    }

    void GameObject::Render()
    {
        for (auto renderableComponent : m_renderableComponents)
            renderableComponent.second->Render();
    }
};