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
    if (transformDef.TransType == ITransform::TransformType::Transform)
    {
      m_transform = std::make_unique<Transform>(*this, transformDef);
    }
    else
    {
      m_transform = std::make_unique<RectTransform>(*this, transformDef);
    }

    LOG_DEBUG("Creating GameObject [ID: %d, Name: '%s']", id, debugName);
  };


  void GameObject::OnDestroy()
  {
    m_transform->OnDestroy();

    ForEachComponent(
      [](IComponent* c)
      {
        c->OnDestroy();
      }
    );
  }

  void GameObject::SendMessageTo(GameObject* receiver, MessageType type)
  {
    Message message;
    message.Sender = this;
    message.Type = type;
    receiver->ReceiveMessage(message);
  }

  void GameObject::ReceiveMessage(Message message)
  {
    m_messageQueue.emplace(message);
  }

  void GameObject::ForEachComponent(FuncOverComponents func)
  {
    for (auto& c : m_components)
      func(c.second.get());
  }

  void GameObject::Update(float dt)
  {
    while (!m_messageQueue.empty())
    {
      Message& message = m_messageQueue.front();
      ForEachComponent(
        [&](IComponent* c)
        {
          c->ProcessMessage(message);
        }
      );
      m_messageQueue.pop();
    }
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

      for (auto& child : m_transform->GetChildren())
      {
        child->SetActive(a);
      }
    }
    else if(!a && m_isActive)
    {
      ForEachComponent(
        [](IComponent* c)
        {
          c->Deactivate();
        }
      );
      for (auto& child : m_transform->GetChildren())
      {
        child->SetActive(a);
      }
    }

    m_isActive = a;
	}
};