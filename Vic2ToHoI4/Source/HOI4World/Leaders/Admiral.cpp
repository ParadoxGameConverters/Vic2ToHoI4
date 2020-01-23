#include "Admiral.h"
#include "OSCompatibilityLayer.h"



HoI4::Admiral::Admiral(const Vic2::Leader* srcLeader, const std::string& portrait):
	name(Utils::convertWin1252ToUTF8(srcLeader->getName())),
	skill(static_cast<int>(srcLeader->getPrestige() * 22.5f) + 1),
	picture(portrait)
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
	maneuveringSkill = skill;
	coordinationSkill = skill;

	/*auto possiblePersonalities = seaPersonalityMap.find(srcLeader->getPersonality());
	if ((possiblePersonalities != seaPersonalityMap.end()) && (possiblePersonalities->second.size() > 0))
	{
		traits.push_back(possiblePersonalities->second[rand() % possiblePersonalities->second.size()]);
	}
	auto possibleBackgrounds = seaBackgroundMap.find(srcLeader->getBackground());
	if ((possibleBackgrounds != seaBackgroundMap.end()) && (possibleBackgrounds->second.size() > 0))
	{
		traits.push_back(possibleBackgrounds->second[rand() % possibleBackgrounds->second.size()]);
	}*/
}