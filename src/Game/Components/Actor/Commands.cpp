#include "Commands.h"

#include "ActorComponent.h"


namespace Game
{
    MoveCommand::MoveCommand(float dx, float dy)
    {
        m_dir = Engine::math::V2fNormalize(sf::Vector2f(dx, dy));
    }

    void MoveCommand::Execute(ActorComponent& actor)
    {
        actor.Move(m_dir);
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

    // --------------------------------------------------------

    FireCommand::FireCommand()
    {
    }

    void FireCommand::Execute(ActorComponent& actor)
    {
        actor.Fire();
    }
};