#include "src/HOI4World/ScenarioCreator/ScenarioCreator.h"
#include "external/common_items/Log.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/HOI4World/ScenarioCreator/Roles/RoleArsenalOfIdeology/RoleArsenalOfIdeology.h"
#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/RoleSpanishCivilWar.h"
#include "src/HOI4World/ScenarioCreator/Roles/RoleTestShell.h"
#include "src/HOI4World/ScenarioCreator/ScenarioConfigParser.h"
#include <filesystem>
#include <ranges>

HoI4::ScenarioCreator::ScenarioCreator(const std::map<std::string, std::shared_ptr<HoI4::Country>>& country_map,
	 const std::string& save_name,
	 const std::string& role_file_name,
	 const date& the_date):
	 save_name_(save_name)
{
	const auto& scenario_file = "Configurables/Scenarios/" + save_name + "_scenario.txt";
	if (std::filesystem::exists(scenario_file))
	{
		// Use pre-genned scenario
		bool pregenned = true;

		const auto& config_parser = ConfigParser(scenario_file, pregenned);
		country_to_role_assignments_ = config_parser.GetRoleAssignments();
		const auto& possible_roles = config_parser.GetPossibleRoles();

		InitialzeRoles(possible_roles, the_date);

		for (const auto& assignment: country_to_role_assignments_)
		{
			const auto& tag = assignment.first;
			const auto& role_name = assignment.second;
			auto& country = country_map.at(tag);

			if (GetRoleByName(role_name)->IsPossible(*country))
			{
				ApplyRole(country, GetRoleByName(role_name));
			}
		}
	}
	else
	{
		// Craft scenario from scratch
		for (const auto& country: country_map | std::views::values)
		{
			countries_.emplace(country);
		}

		const auto& possible_roles = ConfigParser("Configurables/" + role_file_name).GetPossibleRoles();
		InitialzeRoles(possible_roles, the_date);

		for (const auto& country: countries_)
		{
			RecalculateRoleFits(*country);
			ApplyRole(country);
		}
	}
}

void HoI4::ScenarioCreator::InitialzeRoles(const std::set<std::string> possible_roles, const date& the_date)
{
	std::set<std::string> role_tracker = possible_roles;
	if (role_tracker.contains("SpanishCivilWar"))
	{
		roles_.push_back(std::make_shared<RoleSpanishCivilWar>(the_date));
		role_tracker.erase("SpanishCivilWar");
	}
	if (role_tracker.contains("ArsenalOfIdeology"))
	{
		roles_.push_back(std::make_shared<RoleArsenalOfIdeology>());
		role_tracker.erase("ArsenalOfIdeology");
	}
	if (role_tracker.contains("TestShellOne"))
	{
		roles_.push_back(std::make_shared<RoleTestShellOne>());
		role_tracker.erase("TestShellOne");
	}
	if (role_tracker.contains("TestShellTwo"))
	{
		roles_.push_back(std::make_shared<RoleTestShellTwo>());
		role_tracker.erase("TestShellTwo");
	}

	for (const auto& role: role_tracker)
		Log(LogLevel::Warning) << "Unkown identifier " + role + " skipping role in scenario builder.";
}

void HoI4::ScenarioCreator::RecalculateRoleFits(const HoI4::Country& country)
{
	for (const auto& role: roles_)
	{
		role->CalculateFit(country);
	}
	std::sort(roles_.begin(), roles_.end(), Role::RoleComparator);
}

void HoI4::ScenarioCreator::ApplyRole(const std::shared_ptr<HoI4::Country> country)
{
	for (const auto& role: roles_)
	{
		if (role->IsValid(*country))
		{
			ApplyRole(country, role);
			country_to_role_assignments_.emplace(country->getTag(), role->GetName());
			continue;
		}
	}
}

void HoI4::ScenarioCreator::ApplyRole(std::shared_ptr<HoI4::Country> country, const std::shared_ptr<Role> role)
{
	if (auto possible_scenario_mod = role->Apply(country); possible_scenario_mod)
	{
		scenario_mods_.push_back(possible_scenario_mod);
	}
}

const std::shared_ptr<Role> HoI4::ScenarioCreator::GetRoleByName(const std::string role_name)
{
	for (const auto& role: roles_)
	{
		if (role->GetName() == role_name)
			return role;
	}
	return nullptr;
}
