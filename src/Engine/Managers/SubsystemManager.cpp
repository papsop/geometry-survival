#include "SubsystemManager.h"

#include "../Application.h"
#include "../Debug/Logger.h"

namespace Engine
{
    SubsystemManager& SubsystemManager::Get() { return Application::Instance().GetSubsystemManager(); }

    SubsystemManager::SubsystemManager()
        : m_view(std::unique_ptr<ViewSubsystem>(new ViewSubsystem()))
        , m_physics(std::unique_ptr<PhysicsSubsystem>(new PhysicsSubsystem()))
    {

    }

    void SubsystemManager::Update(float dt)
    {

        // ----------- GAME Subsystems
        // order is based on their registration/ID
        for (auto&& subsystem : m_subsystems)
            subsystem->Update(dt);

        // ----------- Static engine Subsystems
        // update collisions
        
        // update physics
        m_physics->Update(dt);
        // update view
        m_view->Update(dt);
    }
};