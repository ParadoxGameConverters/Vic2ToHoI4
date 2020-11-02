#include "Admiral.h"
#include <algorithm>



HoI4::Admiral::Admiral(const Vic2::Leader& srcLeader, const std::string& portrait): Commander(srcLeader, portrait)
{
	maneuveringSkill = varySkill(skill);
	coordinationSkill = std::clamp(static_cast<int>(std::round(srcLeader.getTraitEffectValue("organisation") * 25.0F)) + 1, 1, 7);
}