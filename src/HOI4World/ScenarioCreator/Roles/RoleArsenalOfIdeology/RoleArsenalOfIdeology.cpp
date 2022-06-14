#include "src/HOI4World/ScenarioCreator/Roles/RoleArsenalOfIdeology/RoleArsenalOfIdeology.h"
#include <src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/ModSpanishCivilWar.h>

RoleArsenalOfIdeology::RoleArsenalOfIdeology()
{
	name = "ArsenalOfIdeology";
	instanceCap = 1;
}

bool RoleArsenalOfIdeology::isValid(const HoI4::Country& country) const
{
	return false;
}

void RoleArsenalOfIdeology::calculateFit(const HoI4::Country& country)
{
}

std::shared_ptr<ScenarioMod> RoleArsenalOfIdeology::apply(std::shared_ptr<HoI4::Country> country)
{
	return std::make_shared<ModSpanishCivilWar>();
}
