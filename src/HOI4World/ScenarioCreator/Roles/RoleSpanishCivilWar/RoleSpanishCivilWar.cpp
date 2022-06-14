#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/RoleSpanishCivilWar.h"
#include <src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/ModSpanishCivilWar.h>

RoleSpanishCivilWar::RoleSpanishCivilWar()
{
	name = "SpanishCivilWar";
	instanceCap = 1;
}

bool RoleSpanishCivilWar::isValid(const HoI4::Country& country) const
{
	// Properties to consider validty
	// Don't be a great power
	// Have at least 4 states
	// Have at least 60% of provinces be contigous with capital
	// Have instances below instance cap
	// Ruling party has less than 80% support
	if (instances >= instanceCap || country.isGreatPower())
		return false;
	else
		return true;
}

void RoleSpanishCivilWar::calculateFit(const HoI4::Country& country)
{
	// Factors to affect fitness
	// Contigousness - more contigous the better
	// Divisiveness - more politically divisive the better
	// Size - closer to ~16 states or so the better
	fit = 2;
}

std::shared_ptr<ScenarioMod> RoleSpanishCivilWar::apply(std::shared_ptr<HoI4::Country> country)
{
	instances += 1;

	// Should the modifications to country happen here or in the factory/creator/builder thingy class?
	// Make a copy of country class before messing with it? Does default copy constructor even make a deep copy/work?
	return std::make_shared<ModSpanishCivilWar>(country);
}
