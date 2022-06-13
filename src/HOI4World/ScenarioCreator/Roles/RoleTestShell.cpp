#include "src/HOI4World/ScenarioCreator/Roles/RoleTestShell.h"

bool RoleTestShell::isValid(const HoI4::Country& country) const
{
	return true;
}

void RoleTestShell::calculateFit(const HoI4::Country& country)
{
	if (const auto& name = country.getName(); name)
		fit = name->at(0);
	else
		fit = 0;
}

std::shared_ptr<ScenarioMod> RoleTestShell::apply(const HoI4::Country& country)
{
	return std::shared_ptr<ScenarioMod>();
}
