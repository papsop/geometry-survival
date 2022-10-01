#pragma once

namespace Engine
{
  class IScene
  {
  public:
    IScene() = default;
    ~IScene() = default;

    // Derived class will create it's objects here
    virtual void InstantiateScene() const = 0;
  };

}