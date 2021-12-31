#include "SubsystemManager.h"

#include "../Debug/Logger.h"

namespace Game
{
    SubsystemManager::SubsystemManager()
        : m_physics(std::unique_ptr<PhysicsSubsystem>(new PhysicsSubsystem()))
        , m_view(std::unique_ptr<ViewSubsystem>(new ViewSubsystem()))
        , m_actor(std::unique_ptr<ActorSubsystem>(new ActorSubsystem()))
    {

    }

    void SubsystemManager::Update(float dt)
    {
        m_actor->Update(dt);
        m_physics->Update(dt);

        // always last
        m_view->Update(dt);
    }
};