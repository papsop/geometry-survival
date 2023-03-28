#pragma once
#include <string>
namespace Engine
{
  class GameObject;
}

namespace Game
{
  class ISkill
  {
  public:
    ISkill(const char* skillName, const char* skillDescription)
      : m_skillName(skillName)
      , m_skillDescription(skillDescription) {};
    ~ISkill() = default;

    virtual void Learn(Engine::GameObject* entity) = 0;

    const char* GetSkillName() { return m_skillName; };
    const char* GetSkillDescription() { return m_skillDescription; }

  private:
    const char* m_skillName = "emptySkillName";
    const char* m_skillDescription = "emptySkillDescription";
  };
}