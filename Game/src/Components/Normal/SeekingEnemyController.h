#pragma once
#include "../IComponent.h"
#include "../Normal/ActorComponent.h"
#include <memory>

namespace Game
{
    class SeekingEnemyController : public IComponent
    {
    public:
        SeekingEnemyController(GameObject& obj);
        ~SeekingEnemyController() override = default;

        void SetSeekTarget(std::weak_ptr<GameObject> seekTarget) { m_seekTarget = seekTarget; }
        void OnGameObjectChanged() override;
        void Update(float dt) override;
    private:
        std::weak_ptr<GameObject> m_seekTarget;
        std::weak_ptr<ActorComponent> m_actorComponent;
    };
};


