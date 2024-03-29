#pragma once
#include <Engine/Utils/VectorUtils.h>

namespace Engine
{
  class GameObject;
}

namespace Game
{
  class ActorComponent;
  enum Actor_DamageType;

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

  class DamageCommand : public ICommand
  {
  public:
    DamageCommand(float amount, Engine::GameObject* source, Actor_DamageType type);
    ~DamageCommand() override = default;
    void Execute(ActorComponent& actor) override;
  private:
    float m_amount;
    Engine::GameObject* m_source;
    Actor_DamageType m_type;
  };
};


