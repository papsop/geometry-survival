#include "GameTimer.h"

namespace Game
{

  void GameTimer::Reset()
  {
    m_timerSeconds = 0;
  }

  void GameTimer::Update(float dt)
  {
    m_timerSeconds += dt;
  }

  std::string GameTimer::GetTimerAsString()
  {
    std::string result;

    uint64_t minutes = floorf(GetTimerSeconds() / 60);
    uint64_t seconds = floorf(GetTimerSeconds() - (minutes * 60));

    if (minutes < 10) result = "0"; // leading minutes zero
    result += std::to_string(minutes) + ":";
    if (seconds < 10) result += "0"; // leading seconds zero
    result += std::to_string(seconds);

    return result;
  } 

  float GameTimer::GetTimerSeconds()
  {
    return m_timerSeconds;
  }
}