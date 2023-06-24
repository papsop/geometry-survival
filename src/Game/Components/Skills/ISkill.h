#pragma once

namespace Game
{

	// =========================================================
	class ISkill
	{
	public:
		ISkill() = default;
		virtual ~ISkill() = default;

		virtual void Initialize() { };
		virtual void Clear() { };
	};

	// =========================================================
	class ISkillTeacher
	{
	public:


	};
}