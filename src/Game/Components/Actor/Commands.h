#pragma once
#include <Engine/Utils/VectorUtils.h>

namespace Game
{
    class ActorComponent;

    class ICommand
    {
    public:
        virtual ~ICommand() = default;
        virtual void Execute(ActorComponent& actor) = 0;
    };

    class MoveCommand : public ICommand
    {
    public:
        MoveCommand(float dx, float dy);
        ~MoveCommand() override = default;
        void Execute(ActorComponent& actor) override;
    private:
        Engine::math::Vec2 m_dir;
    };

	class KnockBackCommand : public ICommand
	{
	public:
        KnockBackCommand(float dx, float dy);
		~KnockBackCommand() override = default;
		void Execute(ActorComponent& actor) override;
	private:
		Engine::math::Vec2 m_dir;
	};

    class RotateCommand : public ICommand
    {
    public:
        RotateCommand(float angle);
        ~RotateCommand() override = default;
        void Execute(ActorComponent& actor) override;
    private:
        float m_angle;
    };

    class FireCommand : public ICommand
    {
    public:
        FireCommand();
        ~FireCommand() override = default;
        void Execute(ActorComponent& actor) override;
    private:
    };

	class DamageCommand : public ICommand
	{
	public:
        DamageCommand(float amount);
		~DamageCommand() override = default;
		void Execute(ActorComponent& actor) override;
	private:
        float m_amount;
	};
};


