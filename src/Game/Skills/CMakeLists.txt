set(SKILLS_SOURCE
	ISkill.h
	Skill_AmmoStealer.h
	Skill_AmmoStealer.cpp
	Skill_AmmoPiercer.h
	Skill_AmmoPiercer.cpp
	Skill_BulletDamage.h
	Skill_BulletDamage.cpp
)

target_sources(${GAME_PROJECT} PUBLIC 
	${SKILLS_SOURCE}
)