#include "Commander.h"
#include "OSCompatibilityLayer.h"



HoI4::Commander::Commander(const Vic2::Leader& srcLeader, const std::string& portrait):
	name(Utils::convertWin1252ToUTF8(srcLeader.getName())),
	picture(portrait),
skill(static_cast<int>(srcLeader.getPrestige() * 22.5f) + 1)
{
	if (skill > 5)
	{
		skill = 5;
	}
	else if (skill > 4)
	{
		skill = 4;
	}
	attackSkill = skill;
	defenseSkill = skill;
}
