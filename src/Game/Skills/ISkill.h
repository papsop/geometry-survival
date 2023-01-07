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
    ISkill(std::string skillName, std::string skillDescription)
      : m_skillName(skillName)
      , m_skillDescription(skillDescription) {};
    ~ISkill() = default;

    virtual void Learn(Engine::GameObject* entity) = 0;

    std::string GetSkillName() { return m_skillName; };
    std::string GetSkillDescription() { return m_skillDescription; }

  private:
    std::string m_skillName = "emptySkillName";
    std::string m_skillDescription = "emptySkillDescription";
  };
}