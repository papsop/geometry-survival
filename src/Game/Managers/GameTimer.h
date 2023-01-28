#pragma once
#include <string>

namespace Game
{
  class GameTimer
  {
  public:
    GameTimer() = default;
    ~GameTimer() = default;

    void Reset();
    void Update(float dt);

    std::string GetTimerAsString();
    float GetTimerSeconds();

  private:
    float m_timerSeconds = 0;
  };
}