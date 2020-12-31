#include "General.h"
#include <algorithm>
#include <cmath>



HoI4::General::General(const Vic2::Leader& srcLeader, const std::string& portrait): Commander(srcLeader, portrait)
{
	planningSkill = std::clamp(static_cast<int>(std::round(srcLeader.getTraitEffectValue("morale") * 8.0F)) + 1, 1, 5);
	logisticsSkill =
		 std::clamp(static_cast<int>(std::round(srcLeader.getTraitEffectValue("organisation") * 25.0F)) + 1, 1, 5);
	skill = std::clamp((attackSkill + defenseSkill + planningSkill + logisticsSkill) / 3, 1, 5);
}