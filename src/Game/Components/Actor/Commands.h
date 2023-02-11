#pragma once
#include <Engine/Utils/VectorUtils.h>

namespace Game
{
  class ActorComponent;
  enum Actor_DamageSource;

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
    FireCommand() = default;
    ~FireCommand() override = default;
    void Execute(ActorComponent& actor) override;
  private:
  };

  class ReloadCommand : public ICommand
  {
  public:
    ReloadCommand() = default;
    ~ReloadCommand() override = default;
    void Execute(ActorComponent& actor) override;
  private:
  };

  class DamageCommand : public ICommand
  {
  public:
    DamageCommand(float amount, Actor_DamageSource source);
    ~DamageCommand() override = default;
    void Execute(ActorComponent& actor) override;
  private:
    float m_amount;
    Actor_DamageSource m_source;
  };
};


