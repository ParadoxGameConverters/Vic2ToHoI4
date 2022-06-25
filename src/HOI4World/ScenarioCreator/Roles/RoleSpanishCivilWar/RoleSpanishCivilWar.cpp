#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/RoleSpanishCivilWar.h"
#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/ModSpanishCivilWarBuilder.h"

RoleSpanishCivilWar::RoleSpanishCivilWar(): map_data_(nullptr), all_states_(nullptr)
{
	SetName("SpanishCivilWar");
	SetInstanceCap(1);
}

RoleSpanishCivilWar::RoleSpanishCivilWar(const date& the_date,
	 const std::unique_ptr<Maps::MapData>& map_data,
	 const std::unique_ptr<HoI4::States>& all_states):
	 the_date_(the_date),
	 map_data_(map_data), all_states_(all_states)
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
	// Have a capital state
	if (!IsPossible(country))
	{
		return false;
	}
	if (GetInstances() >= GetInstanceCap() || country.isGreatPower() || country.getLastElection() == date("1836.1.1"))
	{
		return false;
	}

	return true;
}

bool RoleSpanishCivilWar::IsPossible(const HoI4::Country& country) const
{
	if (!country.getCapitalState())
	{
		// May want to log this
		return false;
	}
	if (country.getIdeologySupport().size() < 2)
	{
		return false;
	}
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

	ModSpanishCivilWar::Builder factory(country, the_date_, map_data_, all_states_);
	return factory.Build();
}
