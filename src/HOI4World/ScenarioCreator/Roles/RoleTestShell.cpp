#include "src/HOI4World/ScenarioCreator/Roles/RoleTestShell.h"

// Shell One

bool RoleTestShellOne::isValid(const HoI4::Country& country) const
{
	return country.getMilitaryFactories() > 6;
}

void RoleTestShellOne::calculateFit(const HoI4::Country& country)
{
	fit = country.getMilitaryFactories();
}

std::shared_ptr<ScenarioMod> RoleTestShellOne::apply(std::shared_ptr<HoI4::Country> country)
{
	return nullptr;
}

// Shell Two

bool RoleTestShellTwo::isValid(const HoI4::Country& country) const
{
	return country.getTag()[0] == 'C';
}

void RoleTestShellTwo::calculateFit(const HoI4::Country& country)
{
	double sum = 0;
	for (const auto& letter: country.getTag())
		sum += letter;
	fit = sum;
}

std::shared_ptr<ScenarioMod> RoleTestShellTwo::apply(std::shared_ptr<HoI4::Country> country)
{
	return nullptr;
}
