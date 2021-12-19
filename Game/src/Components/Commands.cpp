#include "Commands.h"

#include "ActorComponent.h"

namespace Game
{
    MoveCommand::MoveCommand(float dx, float dy)
        : m_dx(dx)
        , m_dy(dy)
    {

    }

    void MoveCommand::Execute(ActorComponent& actor)
    {
        actor.Move(m_dx, m_dy);
    }
};