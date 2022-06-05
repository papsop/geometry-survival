#include "GameObject.h"
#include "../../Debug/Logger.h"
#include "../../Managers/GameObjectManager.h"
#include <iostream>

namespace Engine
{
   GameObject::GameObject(uint32_t id, const char* debugName, GameObjectTag tag) 
        : ID(id)
        , DebugName(debugName)
        , Tag(tag)
        , m_transform()
    {
       LOG_DEBUG("Creating GameObject [ID: %d, Name: '%s']", id, debugName);
    };

   void GameObject::ForEachComponent(FuncOverComponents func)
   {
	   for (auto& c : m_components)
		   func(c.second.get());
   }

    void GameObject::OnCollisionStart(GameObject* other)
    {
        ForEachComponent(
            [&](IComponent* c)
            {
                c->OnCollisionStart(other);
            }
        );
    }

	void GameObject::OnCollisionEnd(GameObject* other)
	{
		ForEachComponent(
			[&](IComponent* c)
            {
				c->OnCollisionEnd(other);
			}
		);
	}

    void GameObject::Destroy()
    {
        Engine::GameObjectManager::Get().DestroyGameObject(ID);
    }

	void GameObject::SetActive(bool a)
	{

        // only call callbacks when changing active state
        if (a && !m_isActive)
        {
            ForEachComponent(
                [](IComponent* c)
                {
                    c->Activate();
                }
            );
        }
        else if(!a && m_isActive)
        {
			ForEachComponent(
				[](IComponent* c)
				{
                    c->Deactivate();
				}
			);
        }

        m_isActive = a;
	}
};