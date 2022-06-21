#include "src/HOI4World/ScenarioCreator/Roles/RoleTestShell.h"

// Shell One

bool RoleTestShellOne::IsValid(const HoI4::Country& country) const
{
	return country.getMilitaryFactories() > 6;
}

bool RoleTestShellOne::IsPossible(const HoI4::Country& country) const
{
	return true;
}

void RoleTestShellOne::CalculateFit(const HoI4::Country& country)
{
	SetFit(country.getMilitaryFactories());
}

std::shared_ptr<ScenarioMod> RoleTestShellOne::Apply(std::shared_ptr<HoI4::Country> country)
{
	return nullptr;
}

// Shell Two

bool RoleTestShellTwo::IsValid(const HoI4::Country& country) const
{
	return country.getTag()[0] == 'C';
}

bool RoleTestShellTwo::IsPossible(const HoI4::Country& country) const
{
	return true;
}

void RoleTestShellTwo::CalculateFit(const HoI4::Country& country)
{
	double sum = 0;
	for (const auto& letter: country.getTag())
		sum += letter;
	SetFit(sum);
}

std::shared_ptr<ScenarioMod> RoleTestShellTwo::Apply(std::shared_ptr<HoI4::Country> country)
{
	return nullptr;
}
