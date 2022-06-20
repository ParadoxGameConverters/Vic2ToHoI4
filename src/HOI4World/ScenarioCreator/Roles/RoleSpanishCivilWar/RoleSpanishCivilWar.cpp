#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/RoleSpanishCivilWar.h"
#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/ModSpanishCivilWarBuilder.h"

RoleSpanishCivilWar::RoleSpanishCivilWar()
{
	SetName("SpanishCivilWar");
	SetInstanceCap(1);
}

bool RoleSpanishCivilWar::IsValid(const HoI4::Country& country) const
{
	// Properties to consider validty
	// Don't be a great power
	// Be independant
	// Have at least 4 states
	// Have at least 60% of provinces be contigous with capital
	// Have instances below instance cap
	// Ruling party has less than 80% support
	// Have elections
	if (GetInstances() >= GetInstanceCap() || country.isGreatPower() || country.getLastElection() == date("1836.1.1"))
		return false;
	else
		return true;
}

void RoleSpanishCivilWar::CalculateFit(const HoI4::Country& country)
{
	// Factors to affect fitness
	// Contigousness - more contigous the better
	// Divisiveness - more politically divisive the better
	// Size - closer to ~16 states or so the better
	SetFit(2);
}

std::shared_ptr<ScenarioMod> RoleSpanishCivilWar::Apply(std::shared_ptr<HoI4::Country> country)
{
	SetInstances(GetInstances() + 1);

	// Should the modifications to country happen here or in the factory/creator/builder thingy class?
	// Make a copy of country class before messing with it? Does default copy constructor even make a deep copy/work?
	ModSpanishCivilWar::Builder bui(country);
	return bui.Build();
}
