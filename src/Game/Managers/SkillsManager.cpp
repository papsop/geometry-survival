#include "SkillsManager.h"

#include "../Skills/Skill_AmmoPiercer.h"
#include "../Skills/Skill_AmmoStealer.h"
#include "../Skills/Skill_BulletDamage.h"
#include "../Skills/Skill_PickupRadius.h"
#include "../Skills/Skill_BurningAmmo.h"

#include <cstdlib>
#include <time.h>

namespace Game
{

  SkillsManager::SkillsManager(Engine::Application& app)
    : m_app(app)
  {

  }

  void SkillsManager::VirtualOnInit()
  {
    std::srand((unsigned)time(NULL));
    ResetToDefaultSkills();
  }

  void SkillsManager::ResetToDefaultSkills()
  {
    m_availableSkills.clear();
    m_availableSkills.push_back(std::make_unique<Skill_AmmoPiercer>());
    m_availableSkills.push_back(std::make_unique<Skill_AmmoStealer>());
    m_availableSkills.push_back(std::make_unique<Skill_BulletDamage>());
    m_availableSkills.push_back(std::make_unique<Skill_PickupRadius>());
    m_availableSkills.push_back(std::make_unique<Skill_BurningAmmo>());
  }

  std::vector< ISkill* > SkillsManager::GetNRandomSkills(int N)
  {
    DD_ASSERT(N < m_availableSkills.size(), "Trying to retrieve more skills than available");

    for (int i = m_availableSkills.size() -1 ; i > 0; i--)
    {
      int index = std::rand() % (i+1);
      std::swap(m_availableSkills[i], m_availableSkills[index]);
    }

    std::vector< ISkill* > result;
    for (int i = 0; i < N; i++)
    {
      result.push_back(m_availableSkills[i].get());
    }
    return result;
  }

}