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
    }

    void SeekingEnemyController::Update(float dt)
    {
        if (auto tmpSeekTarget = m_seekTarget.lock())
        {
            if (auto tmpActor = m_actorComponent.lock())
            {
                tmpActor->RotateTo(tmpSeekTarget->GetTransform().Position);
            }
        }
    }
};