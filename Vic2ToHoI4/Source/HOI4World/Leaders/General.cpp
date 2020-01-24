#include "General.h"



HoI4::General::General(const Vic2::Leader& srcLeader, const std::string& portrait):
	Commander(srcLeader, portrait)
{
	planningSkill = varySkill(skill);
	logisticsSkill = varySkill(skill);
}