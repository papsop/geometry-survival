#include "SubsystemManager.h"

#include "../Debug/Logger.h"

namespace Game
{
    SubsystemManager::SubsystemManager()
        : m_physics(std::unique_ptr<PhysicsSubsystem>(new PhysicsSubsystem()))
    {

    }

    void SubsystemManager::Update(float dt)
    {
        //LOG_INFO("Updating SubsystemManager");

        m_physics->Update(dt);
    }
};