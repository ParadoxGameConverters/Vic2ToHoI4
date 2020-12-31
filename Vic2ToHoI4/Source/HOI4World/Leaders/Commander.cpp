#include "Commander.h"
#include "OSCompatibilityLayer.h"
#include <algorithm>
#include <cmath>
#include <random>



HoI4::Commander::Commander(const Vic2::Leader& srcLeader, std::string portrait):
	 name(commonItems::convertWin1252ToUTF8(srcLeader.getName())), picture(std::move(portrait))
{
	attackSkill = std::clamp(static_cast<int>(std::round(srcLeader.getTraitEffectValue("attack"))) + 1, 1, 7);
	defenseSkill = std::clamp(static_cast<int>(std::round(srcLeader.getTraitEffectValue("defence"))) + 1, 1, 7);
}