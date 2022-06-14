#include "src/HOI4World/ScenarioCreator/ScenarioCreator.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/HOI4World/ScenarioCreator/Roles/RoleArsenalOfIdeology/RoleArsenalOfIdeology.h"
#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/RoleSpanishCivilWar.h"
#include "src/HOI4World/ScenarioCreator/ScenarioConfigParser.h"
#include <external/common_items/Log.h>
#include <filesystem>
#include <ranges>

HoI4::ScenarioCreator::ScenarioCreator(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countryMap,
	 const std::string& saveName):
	 saveName(saveName)
{
	const auto& scenarioFile = "Configurables/Scenarios/" + saveName + "_scenario.txt";
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

			applyRole(countryMap.at(tag), getRoleByName(roleName));
		}
	}
	else
	{
		// Craft scenario from scratch
		for (const auto& country: countryMap | std::views::values)
		{
			countries.emplace(country);
		}

		const auto& possibleRoles = ConfigParser("Configurables/scenario_creator_roles.txt").getPossibleRoles();
		initialzeRoles(possibleRoles);

		for (const auto& country: countries)
		{
			recalculateRoleFits(*country);
			applyRole(country);
		}
	}
}

void HoI4::ScenarioCreator::initialzeRoles(const std::set<std::string> possibleRoles)
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

void HoI4::ScenarioCreator::recalculateRoleFits(const HoI4::Country& country)
{
	for (const auto& role: roles)
	{
		role->calculateFit(country);
	}
	std::sort(roles.begin(), roles.end(), Role::roleComparator);
}

void HoI4::ScenarioCreator::applyRole(const std::shared_ptr<HoI4::Country> country)
{
	for (const auto& role: roles)
	{
		if (role->isValid(*country))
		{
			applyRole(country, role);
			countryToRoleAssignments.emplace(country->getTag(), role->getName());
			continue;
		}
	}
}

void HoI4::ScenarioCreator::applyRole(std::shared_ptr<HoI4::Country> country, const std::shared_ptr<Role> role)
{
	if (auto possibleScenarioMod = role->apply(country); possibleScenarioMod)
	{
		scenarioMods.push_back(possibleScenarioMod);
	}
}

const std::shared_ptr<Role> HoI4::ScenarioCreator::getRoleByName(const std::string roleName)
{
	for (const auto& role: roles)
	{
		if (role->getName() == roleName)
			return role;
	}
	return nullptr;
}
