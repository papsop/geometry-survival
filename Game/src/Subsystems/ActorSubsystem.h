#pragma once

#include <vector>
#include "../Components/Actor.h"
#include "../Components/Player.h"

namespace Game
{
    class SubsystemManager;

    class ActorSubsystem
    {
    public:
        ~ActorSubsystem();

        void RegisterComponent(IComponent* component);
        void UnregisterComponent(IComponent* component);

        void Update(float dt);

    private:
        ActorSubsystem();

        std::vector< InputComponent* > m_inputs;
        std::vector< ActorComponent* > m_actors;

        friend class SubsystemManager;
    };
};


