#include "Commands.h"

#include "ActorComponent.h"


namespace Game
{
    MoveCommand::MoveCommand(float dx, float dy)
    {
        m_dir = Engine::math::V2fNormalize(Engine::math::Vec2(dx, dy));
    }

    void MoveCommand::Execute(ActorComponent& actor)
    {
        actor.Move(m_dir);
    }

	// --------------------------------------------------------
    KnockBackCommand::KnockBackCommand(float dx, float dy)
	{
		m_dir = Engine::math::V2fNormalize(Engine::math::Vec2(dx, dy));
	}

	void KnockBackCommand::Execute(ActorComponent& actor)
	{
        actor.KnockBack(m_dir);
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
    void FireCommand::Execute(ActorComponent& actor)
    {
        actor.WeaponFire();
    }

    // --------------------------------------------------------
	void ReloadCommand::Execute(ActorComponent& actor)
	{
		actor.WeaponReload();
	}

	// --------------------------------------------------------
    DamageCommand::DamageCommand(float amount)
        : m_amount(amount) {};

	void DamageCommand::Execute(ActorComponent& actor)
	{
        actor.ApplyDamage(m_amount);
	}

};