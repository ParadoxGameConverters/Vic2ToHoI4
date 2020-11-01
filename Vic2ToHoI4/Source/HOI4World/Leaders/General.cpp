#include "General.h"
#include <algorithm>


HoI4::General::General(const Vic2::Leader& srcLeader, const std::string& portrait):
	Commander(srcLeader, portrait)
{
	planningSkill = varySkill(skill);
	logisticsSkill = std::clamp(static_cast<int>(std::round(srcLeader.getTraitEffectValue("organisation") * 25.0F)) + 1, 1, 5);
}