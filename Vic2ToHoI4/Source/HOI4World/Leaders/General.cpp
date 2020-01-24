#include "General.h"
#include "OSCompatibilityLayer.h"



HoI4::General::General(const Vic2::Leader& srcLeader, const std::string& portrait):
	Commander(srcLeader, portrait)
{
	planningSkill = skill;
	logisticsSkill = skill;
}