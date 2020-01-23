#include "General.h"
#include "OSCompatibilityLayer.h"



HoI4::General::General(const Vic2::Leader* srcLeader, const std::string& portrait):
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
	planningSkill = skill;
	logisticsSkill = skill;

	/*auto possiblePersonalities = landPersonalityMap.find(srcLeader->getPersonality());
	if ((possiblePersonalities != landPersonalityMap.end()) && (possiblePersonalities->second.size() > 0))
	{
		traits.push_back(possiblePersonalities->second[rand() % possiblePersonalities->second.size()]);
	}
	auto possibleBackgrounds = landBackgroundMap.find(srcLeader->getBackground());
	if ((possibleBackgrounds != landBackgroundMap.end()) && (possibleBackgrounds->second.size() > 0))
	{
		traits.push_back(possibleBackgrounds->second[rand() % possibleBackgrounds->second.size()]);
	}*/
}