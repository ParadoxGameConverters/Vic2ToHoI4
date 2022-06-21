#include "src/HOI4World/ScenarioCreator/Roles/RoleArsenalOfIdeology/RoleArsenalOfIdeology.h"
#include <src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/ModSpanishCivilWar.h>

RoleArsenalOfIdeology::RoleArsenalOfIdeology()
{
	SetName("ArsenalOfIdeology");
	SetInstanceCap(1);
}

bool RoleArsenalOfIdeology::IsValid(const HoI4::Country& country) const
{
	return false;
}

bool RoleArsenalOfIdeology::IsPossible(const HoI4::Country& country) const
{
	return true;
}

void RoleArsenalOfIdeology::CalculateFit(const HoI4::Country& country)
{
}

std::shared_ptr<ScenarioMod> RoleArsenalOfIdeology::Apply(std::shared_ptr<HoI4::Country> country)
{
	return std::make_shared<ModSpanishCivilWar>();
}
