#ifndef SCENARIO_CREATOR_H
#define SCENARIO_CREATOR_H

#include "src/HOI4World/ScenarioCreator/Roles/Role.h"

namespace HoI4
{

class ScenarioCreator
{
  public:
	typedef std::multiset<std::shared_ptr<HoI4::Country>, decltype(HoI4::Country::compareCountriesByIndustryDescending)*>
		 CountriesByIndustryDescendingMultiSet;

	class Builder;
	ScenarioCreator() = default;
	ScenarioCreator(const std::map<std::string, std::shared_ptr<HoI4::Country>>& country_map,
		 const std::string& save_name,
		 const std::string& role_file_name = "scenario_creator_roles.txt");

	[[nodiscard]] const auto& GetRoles() const { return roles_; };
	[[nodiscard]] const auto& GetScenarioMods() const { return scenario_mods_; };
	[[nodiscard]] const auto& GetCountries() const { return countries_; };
	[[nodiscard]] const auto& GetAssignments() const { return country_to_role_assignments_; };
	[[nodiscard]] const auto& GetSaveName() const { return save_name_; };


  private:
	// Initializes only the roles specified in scenario_creator_roles.txt
	void InitialzeRoles(const std::set<std::string> possible_roles);

	// Sorts roles_ vector by fit to parameter country
	void RecalculateRoleFits(const HoI4::Country& country);

	// Apply role to country, only if a valid match exists. Update tag -> Role assignments.
	void ApplyRole(std::shared_ptr<HoI4::Country> country);

	// Apply role to country, ignore all restrictions and collect possible resulting mod.
	void ApplyRole(std::shared_ptr<HoI4::Country> country, const std::shared_ptr<Role> role);

	const std::shared_ptr<Role> GetRoleByName(const std::string role_name);

	std::vector<std::shared_ptr<Role>> roles_;
	std::vector<std::shared_ptr<ScenarioMod>> scenario_mods_;
	CountriesByIndustryDescendingMultiSet countries_{HoI4::Country::compareCountriesByIndustryDescending};
	std::map<std::string, std::string> country_to_role_assignments_;
	std::string save_name_;
};

} // namespace HoI4

#endif // SCENARIO_CREATOR_H