#include "ActorComponent.h"
#include "WeaponComponent.h"
#include "RPGComponent.h"

#include <Engine/Components/Physics.h>
#include <Engine/Application.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/ComponentManager.h>

#include "../../Managers/GameManager.h"
#include "../../Core/GameObject/GameObjectFactory.h"
#include "WeaponComponent.h"

namespace Game
{
  ActorComponent::ActorComponent(Engine::GameObject& obj)
    : IComponent(obj)
    , m_commandsQueue()
  {
    SetRequiredComponents<Engine::PhysicsBodyComponent, RPGComponent>();
  }

  void ActorComponent::VirtualOnCreate()
  {
    m_RPGComponent = Owner.GetComponent<RPGComponent>();
    m_spriteComponent = Owner.GetComponent<Engine::SpriteDrawableComponent>(); // not required

    Engine::ComponentManager::Get().RegisterComponent(this);
  }

  ActorComponent::~ActorComponent()
  {
    Engine::ComponentManager::Get().UnregisterComponent(this);
  }

	void ActorComponent::VirtualOnActivated()
	{
		IEventListener<event::E_GameStateChanged>::RegisterListener();
	}

	void ActorComponent::VirtualOnDeactivated()
	{
		IEventListener<event::E_GameStateChanged>::UnregisterListener();
	}

  void ActorComponent::Move(Engine::math::Vec2 dir)
  {
    auto physBody = Owner.GetComponent<Engine::PhysicsBodyComponent>();
    physBody->SetLinearVelocity(dir, m_RPGComponent->GetStat(RPGStats::MOVEMENT_SPEED));

		m_isMoving = !(dir.x == 0 && dir.y == 0);
		m_movingDir = dir;

    if (m_spriteComponent)
    {
      if (dir.x < 0 && !isFlipped)
      {
        m_spriteComponent->FlipX();
        isFlipped = true;
      }
      else if (dir.x > 0 && isFlipped)
      {
        m_spriteComponent->FlipX();
        isFlipped = false;
      }
    }
  }

  void ActorComponent::KnockBack(Engine::math::Vec2 dir)
	{
    auto physBody = Owner.GetComponent<Engine::PhysicsBodyComponent>();
    auto mass = physBody->GetMass();

    auto actualVelocity = physBody->GetLinearVelocity();
    dir *= 2.0f;
    auto desiredVelocity = dir;

    auto impulse = (desiredVelocity - actualVelocity);
    impulse *= mass;
    physBody->ApplyImpulseToCenter(impulse);
  }

  void ActorComponent::Rotate(float angle)
  {
    auto physBody = Owner.GetComponent<Engine::PhysicsBodyComponent>();
    physBody->GetB2Body()->SetTransform(Owner.GetTransform()->GetPosition(), angle);
    physBody->GetB2Body()->SetAngularVelocity(0);
  }

	void ActorComponent::ApplyDamage(float amount, Engine::GameObject* source, Actor_DamageType type)
	{
    auto currentHP = m_RPGComponent->GetStat(RPGStats::CURRENT_HEALTH);
    m_RPGComponent->SetStatBase(RPGStats::CURRENT_HEALTH, currentHP - amount);

    if (amount > 1.0f)
    {
			CombatTextDef combatTextDef;
			combatTextDef.Damage = amount;
			combatTextDef.Position = Owner.GetTransform()->GetPosition();
			GameObjectFactory::CreateCombatTextObject(combatTextDef);
    }

//     if (source == Actor_DamageSource::Bullet)
//     {
//       //Owner.SendMessageTo(&Owner, Engine::MessageType::Actor_TookDamage_Knockback);
//     }
//     else
//     {
//       //Owner.SendMessageTo(&Owner, Engine::MessageType::Actor_TookDamage_NoKnockback);
//     }

    DamageTakenData eventData;
    eventData.Amount = amount;
		eventData.Source = source;
		eventData.Type   = type;
    OnDamageTaken.Invoke(eventData);

		if (m_RPGComponent->GetStat(RPGStats::CURRENT_HEALTH) <= 0.0f)
		{
      this->OnZeroHealth.Invoke();
		}
      
	}

	void ActorComponent::Debug(Engine::view::IViewStrategy* viewStrategy)
	{
    // name
    Engine::math::Vec2 pos = Owner.GetTransform()->GetPosition() + Engine::math::Vec2(0.0f, 3.0f);
    viewStrategy->DebugRenderText(Engine::ITransform::PositionSpace::WorldSpace, Owner.DebugName, pos, true, 12.0f, sf::Color::Yellow);

    // currentHealth/maxHealth
		pos = Owner.GetTransform()->GetPosition() + Engine::math::Vec2(0.0f, 4.0f);
    std::string healthString = "HP " + std::to_string(static_cast<int>(m_RPGComponent->GetStat(RPGStats::CURRENT_HEALTH))) + \
                                  "/" + \
                                std::to_string( static_cast<int>(m_RPGComponent->GetStat(RPGStats::MAX_HEALTH)) );

		viewStrategy->DebugRenderText(Engine::ITransform::PositionSpace::WorldSpace, healthString, pos, true, 12.0f, sf::Color::Yellow);
	}	
  
  void ActorComponent::ReceiveEvent(const event::E_GameStateChanged& eventData)
	{
		SetEnabled(eventData.NewState == GameState::Gameplay);

    if(!IsEnabled())
      Move({ 0.0f, 0.0f }); // to stop the movement of the actor
	}

	void ActorComponent::Update(float dt)
  {
    while (!m_commandsQueue.empty())
    {
      m_commandsQueue.front()->Execute(*this);
      m_commandsQueue.pop();
    }
  }
};