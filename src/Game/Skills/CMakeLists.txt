set(SKILLS_SOURCE
	ISkill.h
	Skill_AmmoStealer.h
	Skill_AmmoStealer.cpp
)

target_sources(${GAME_PROJECT} PUBLIC 
	${SKILLS_SOURCE}
)