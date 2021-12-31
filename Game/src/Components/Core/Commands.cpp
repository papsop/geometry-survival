#include "Commands.h"

#include "../Actor.h"

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

    // --------------------------------------------------------

    RotateCommand::RotateCommand(float angle)
        : m_angle(angle)
    {

    }

    void RotateCommand::Execute(ActorComponent& actor)
    {
        actor.Rotate(m_angle);
    }
};