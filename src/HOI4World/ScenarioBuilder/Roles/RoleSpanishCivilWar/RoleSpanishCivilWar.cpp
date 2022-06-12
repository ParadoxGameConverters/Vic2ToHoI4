#include "src/HOI4World/ScenarioBuilder/Roles/RoleSpanishCivilWar/RoleSpanishCivilWar.h"

RoleSpanishCivilWar::RoleSpanishCivilWar()
{
	name = "SpanishCivilWar";
	instanceCap = 1;
}

bool RoleSpanishCivilWar::isValid(const HoI4::Country& country) const
{
	return false;
}

void RoleSpanishCivilWar::calculateFit(const HoI4::Country& country)
{
	fit = 2;
}

std::shared_ptr<ScenarioMod> RoleSpanishCivilWar::apply(const HoI4::Country& country)
{
	return std::make_shared<ScenarioMod>(); // Mod Factory time
}
