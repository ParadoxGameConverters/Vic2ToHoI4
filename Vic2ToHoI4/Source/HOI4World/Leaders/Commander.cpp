#include "Commander.h"
#include "OSCompatibilityLayer.h"
#include <algorithm>
#include <random>



HoI4::Commander::Commander(const Vic2::Leader& srcLeader, std::string portrait):
	 name(commonItems::convertWin1252ToUTF8(srcLeader.getName())),
	picture(std::move(portrait)),
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

	attackSkill = std::clamp(static_cast<int>(std::round(srcLeader.getTraitEffectValue("attack"))) + 1, 1, 7);
	defenseSkill = varySkill(skill);
}


static std::mt19937 randomnessEngine;
static std::uniform_int_distribution<> numberDistributor(-1, 2); // due to int truncation, this is -1 to 1 in practice

int HoI4::Commander::varySkill(int skill) const
{
	skill += numberDistributor(randomnessEngine) - 1;
	return std::clamp(skill, 1, 5);
}

