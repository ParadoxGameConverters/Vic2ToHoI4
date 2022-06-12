#include "src/HOI4World/ScenarioBuilder/Roles/RoleArsenalOfIdeology/RoleArsenalOfIdeology.h"

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

void RoleArsenalOfIdeology::apply(const HoI4::Country& country)
{
}
