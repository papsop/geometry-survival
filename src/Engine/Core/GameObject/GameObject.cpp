#include "GameObject.h"
#include "../../Debug/Logger.h"
#include "../../Managers/GameObjectManager.h"
#include "../../Managers/PhysicsManager.h"
#include <iostream>

namespace Engine
{
   GameObject::GameObject(uint32_t id, const char* debugName, GameObjectTag tag, const ITransform::TransformDefinition& transformDef)
        : ID(id)
        , DebugName(debugName)
        , Tag(tag)
    { 
       m_transform = std::make_unique<Transform>(*this, transformDef);
       LOG_DEBUG("Creating GameObject [ID: %d, Name: '%s']", id, debugName);
    };

   void GameObject::SendMessageTo(GameObject* receiver, MessageType type)
   {
       Message message;
       message.Sender = this;
       message.Type = type;
       receiver->ReceiveMessage(message);
   }

   void GameObject::ReceiveMessage(const Message& message)
   {
       ForEachComponent(
           [&](IComponent* c)
           {
               c->ProcessMessage(message);
           }
       );
   }

   void GameObject::ForEachComponent(FuncOverComponents func)
   {
	   for (auto& c : m_components)
		   func(c.second.get());
   }

    void GameObject::OnCollisionStart(CollisionData& collision)
    {
        ForEachComponent(
            [&](IComponent* c)
            {
                c->OnCollisionStart(collision);
            }
        );
    }

	void GameObject::OnCollisionEnd(CollisionData& collision)
	{
		ForEachComponent(
			[&](IComponent* c)
            {
				c->OnCollisionEnd(collision);
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