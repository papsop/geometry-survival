#pragma once
namespace Engine
{
  class GameObject;
}

namespace Game
{
  class ISkill
  {
  public:
    ISkill() = default;
    ~ISkill() = default;

    virtual void Learn(Engine::GameObject* entity) = 0;
  };
}