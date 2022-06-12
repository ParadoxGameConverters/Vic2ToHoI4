#ifndef SCENARIO_BUILDER_H
#define SCENARIO_BUILDER_H

#include "src/HOI4World/ScenarioBuilder/Roles/Role.h"

namespace HoI4
{

class ScenarioBuilder
{
  public:
	ScenarioBuilder() = default;
	ScenarioBuilder(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countryMap,
		 const std::string& saveName);

	typedef std::multiset<std::shared_ptr<HoI4::Country>, decltype(&HoI4::Country::compareCountriesByIndustry)>
		 CountriesByIndustryMultiSet;

	[[nodiscard]] std::vector<std::shared_ptr<Role>> getRoles() const { return roles; };
	[[nodiscard]] std::vector<std::shared_ptr<ScenarioMod>> getScenarioMods() const { return scenarioMods; };
	[[nodiscard]] CountriesByIndustryMultiSet getCountries() const { return countries; };
	[[nodiscard]] std::map<std::string, std::string> getAssignments() const { return countryToRoleAssignments; };


  private:
	// NOTE: does more than one ptr to each obj need to exist at a time? could unique_ptr work?
	std::vector<std::shared_ptr<Role>> roles;
	std::vector<std::shared_ptr<ScenarioMod>> scenarioMods;
	CountriesByIndustryMultiSet countries;
	std::map<std::string, std::string> countryToRoleAssignments;

	// Construct and emplace a role of each class
	void initialzeRoles(const std::set<std::string> possibleRoles);

	// For a given country, update all role fit values and sort container
	void recalculateRoleFits(const HoI4::Country& country);

	// Apply role to country, only if a valid match exists. Update tag -> Role assignments.
	void applyRole(const HoI4::Country& country);

	// Apply role to country, ignore all restrictions and collect possible resulting mod.
	void applyRole(const HoI4::Country& country, const std::shared_ptr<Role> role);


	const std::shared_ptr<Role> getRoleByName(const std::string roleName);
};

} // namespace HoI4

#endif // SCENARIO_BUILDER