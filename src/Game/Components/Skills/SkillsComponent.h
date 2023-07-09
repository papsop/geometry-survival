#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>

#include "ISkill.h"

#include <memory>
#include <vector>
namespace Game
{
	class SkillsComponent : public Engine::IComponent
	{
	public:
		SkillsComponent(Engine::GameObject& obj);
		virtual ~SkillsComponent() override;

		void AddSkill(std::unique_ptr<ISkill> skill);

		// TODO: RemoveSkill? not needed right now

	private:
		std::vector< std::unique_ptr<ISkill> > m_skills;
	};
}