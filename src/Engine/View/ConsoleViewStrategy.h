#pragma once
#include "IViewStrategy.h"

#include <SFML/Graphics.hpp>

namespace Engine{
namespace view{
  class ConsoleViewStrategy : public IViewStrategy
  {
  public:
    ConsoleViewStrategy(ViewManager& viewManager);
    ~ConsoleViewStrategy() = default;

    void PollEvents() override;

    void PreRender() override;
    void PostRender() override;
    sf::Vector2f GetMousePosition() override { return { 0,0 }; }; // placeholder
  };
}};