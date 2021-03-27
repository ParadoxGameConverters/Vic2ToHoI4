#include "Admiral.h"
#include <algorithm>
#include <cmath>



HoI4::Admiral::Admiral(const Vic2::Leader& srcLeader): Commander(srcLeader)
{
	maneuveringSkill =
		 std::clamp(static_cast<int>(std::round(srcLeader.getTraitEffectValue("morale") * 8.0F)) + 1, 1, 7);
	coordinationSkill =
		 std::clamp(static_cast<int>(std::round(srcLeader.getTraitEffectValue("organisation") * 25.0F)) + 1, 1, 7);
	skill = std::clamp((attackSkill + defenseSkill + maneuveringSkill + coordinationSkill) / 3, 1, 5);
}