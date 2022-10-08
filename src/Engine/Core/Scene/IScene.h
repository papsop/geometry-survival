#pragma once

namespace Engine
{
  class IScene
  {
  public:
    IScene() = default;
    ~IScene() = default;

    virtual void InstantiateObjects() const = 0;
  };

}