#pragma once

namespace Game
{
	class SkillsComponent;
	// =========================================================
	class ISkill
	{
	public:
		ISkill(const char* name) : m_skillName(name) {};
		virtual ~ISkill() = default;

		virtual void Init(SkillsComponent& owner) { };
		virtual void Clear(SkillsComponent& owner) { };

		const char* GetSkillName() { return m_skillName; };
	protected:
		const char* m_skillName;
	};

	// =========================================================
	class ISkillTeacher
	{
	public:


	};
}