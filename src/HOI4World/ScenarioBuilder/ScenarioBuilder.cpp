#include "src/HOI4World/ScenarioBuilder/ScenarioBuilder.h"
#include "src/HOI4World/ScenarioBuilder/Roles/RoleArsenalOfIdeology.h"
#include "src/HOI4World/ScenarioBuilder/Roles/RoleSpanishCivilWar.h"
#include "src/HOI4World/ScenarioBuilder/ScenarioConfigParser.h"
#include <ranges>

HoI4::ScenarioBuilder::ScenarioBuilder(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countryMap,
	 const std::string fileName)
{
	// If a certain file exists, read it to get possibleRoles and
	for (const auto& country: countryMap | std::views::values)
	{
		countries.emplace(country);
	}

	const auto& possibleRoles = ConfigParser(fileName).getPossibleRoles();
	initialzeRoles(possibleRoles);

	for (const auto& country: countries)
	{
		recalculateRoleFits(*country);
		applyRole(*country);
	}
}

void HoI4::ScenarioBuilder::initialzeRoles(const std::set<std::string> possibleRoles)
{
	if (possibleRoles.contains("SpanishCivilWar"))
		roles.push_back(std::make_shared<RoleSpanishCivilWar>());
	if (possibleRoles.contains("ArsenalOfIdeology"))
		roles.push_back(std::make_shared<RoleArsenalOfIdeology>());
}

void HoI4::ScenarioBuilder::recalculateRoleFits(const HoI4::Country& country)
{
	for (const auto& role: roles)
	{
		role->calculateFit(country);
	}
	std::sort(roles.begin(), roles.end(), Role::roleComparator);
}

void HoI4::ScenarioBuilder::applyRole(const HoI4::Country& country)
{
	for (const auto& role: roles)
	{
		if (role->isValid(country))
		{
			role->apply(country);
			continue;
		}
	}
}
