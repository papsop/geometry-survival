#include "SeekingEnemyController.h"

#include "../../GameObject.h"

namespace Game
{
    SeekingEnemyController::SeekingEnemyController(GameObject& obj)
        : IUpdatableComponent(obj)
    {
    }

    void SeekingEnemyController::Init()
    {
        m_actorComponent = m_owner.GetComponent<ActorComponent>();
        if (auto tmpRigidbody = m_owner.GetComponent<RigidbodyComponent>().lock())
        {
            tmpRigidbody->m_maxMovementSpeed = 50.0f;
        }
    }

    void SeekingEnemyController::Update(float dt)
    {
        if (auto tmpSeekTarget = m_seekTarget.lock())
        {
            if (auto tmpActor = m_actorComponent.lock())
            {
                tmpActor->SetMovementVector(m_owner.GetTransform().Forward());
                tmpActor->RotateTo(tmpSeekTarget->GetTransform().Position);
            }
        }
    }
};