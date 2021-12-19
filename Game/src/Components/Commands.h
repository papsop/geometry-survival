#pragma once

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
        float m_dx;
        float m_dy;
    };
};


