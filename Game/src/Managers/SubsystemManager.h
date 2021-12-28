#pragma once
#include "../Subsystems/AllSubsystems.h"

#include <unordered_map>
#include <memory>

namespace Game
{
    class Application;
    class SubsystemManager
    {

    public:
        ~SubsystemManager() = default;

        void Update(float dt);

        std::unique_ptr<PhysicsSubsystem> m_physics;
    private:
        SubsystemManager();

    friend class Application; // only Application can create a manager
    };
};