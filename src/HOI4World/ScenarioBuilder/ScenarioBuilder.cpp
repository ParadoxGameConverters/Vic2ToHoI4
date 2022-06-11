#include "src/HOI4World/ScenarioBuilder/ScenarioBuilder.h"
#include "src/HOI4World/ScenarioBuilder/Roles/RoleArsenalOfIdeology.h"
#include "src/HOI4World/ScenarioBuilder/Roles/RoleSpanishCivilWar.h"
#include "src/HOI4World/ScenarioBuilder/ScenarioConfigParser.h"
#include <filesystem>
#include <ranges>
#include <external/common_items/Log.h>

HoI4::ScenarioBuilder::ScenarioBuilder(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countryMap,
	 const std::string& saveName)
{
	const auto& scenarioFile = "configurables/scenarios/" + saveName + "_scenario.txt";
	if (std::filesystem::exists(scenarioFile))
	{
		// Use pre-genned scenario
		bool preGenned = true;

		const auto& configParser = ConfigParser(scenarioFile, preGenned);
		countryToRoleAssignments = configParser.getRoleAssignments();
		const auto& possibleRoles = configParser.getPossibleRoles();

		initialzeRoles(possibleRoles);

		for (const auto& assignment: countryToRoleAssignments)
		{
			const auto& tag = assignment.first;
			const auto& roleName = assignment.second;

			applyRolePreGen(*countryMap.at(tag), getRoleByName(roleName));
		}
	}
	else
	{
		// Craft scenario from scratch
		for (const auto& country: countryMap | std::views::values)
		{
			countries.emplace(country);
		}

		const auto& possibleRoles = ConfigParser("configurables/ScenarioBuilderRoles.txt").getPossibleRoles();
		initialzeRoles(possibleRoles);

		for (const auto& country: countries)
		{
			recalculateRoleFits(*country);
			applyRole(*country);
		}
	}
}

void HoI4::ScenarioBuilder::initialzeRoles(const std::set<std::string> possibleRoles)
{
	auto roleTracker = possibleRoles;
	if (roleTracker.contains("SpanishCivilWar"))
	{
		roles.push_back(std::make_shared<RoleSpanishCivilWar>());
		roleTracker.erase("SpanishCivilWar");
	}
	if (roleTracker.contains("ArsenalOfIdeology"))
	{
		roles.push_back(std::make_shared<RoleArsenalOfIdeology>());
		roleTracker.erase("ArsenalOfIdeology");
	}

	for (const auto& role: roleTracker)
		Log(LogLevel::Warning) << "Unkown identifier " + role + " skipping role in scenario builder.";
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
			countryToRoleAssignments.emplace(country.getTag(), role->getName());
			continue;
		}
	}
}

void HoI4::ScenarioBuilder::applyRolePreGen(const HoI4::Country& country, const std::shared_ptr<Role> role)
{
	role->apply(country);
}

const std::shared_ptr<Role> HoI4::ScenarioBuilder::getRoleByName(const std::string roleName)
{
	for (const auto& role: roles)
	{
		if (role->getName() == roleName)
			return role;
	}
	return nullptr;
}
