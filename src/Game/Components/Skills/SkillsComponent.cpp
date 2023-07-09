#include "SkillsComponent.h"

namespace Game
{

	SkillsComponent::SkillsComponent(Engine::GameObject& obj)
		: IComponent(obj)
	{

	}

	SkillsComponent::~SkillsComponent()
	{
		for (auto& skill : m_skills)
		{
			skill->Clear(*this);
		}

		m_skills.clear();
	}

	void SkillsComponent::AddSkill(std::unique_ptr<ISkill> skill)
	{
		LOG_ERROR("Adding skill: %s", skill->GetSkillName());
		skill->Init(*this);
		m_skills.push_back(std::move(skill));
	}

}