#ifndef SCENARIO_CREATOR_H
#define SCENARIO_CREATOR_H

#include "src/HOI4World/ScenarioCreator/Roles/Role.h"

namespace HoI4
{

class ScenarioCreator
{
  public:
	ScenarioCreator() = default;
	ScenarioCreator(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countryMap,
		 const std::string& saveName);

	typedef std::multiset<std::shared_ptr<HoI4::Country>, decltype(HoI4::Country::compareCountriesByIndustryDescending)*>
		 CountriesByIndustryDescendingMultiSet;

	[[nodiscard]] const auto& getRoles() const { return roles; };
	[[nodiscard]] const auto& getScenarioMods() const { return scenarioMods; };
	[[nodiscard]] const auto& getCountries() const { return countries; };
	[[nodiscard]] const auto& getAssignments() const { return countryToRoleAssignments; };
	[[nodiscard]] const auto& getSaveName() const { return saveName; };


  private:
	std::vector<std::shared_ptr<Role>> roles;
	std::vector<std::shared_ptr<ScenarioMod>> scenarioMods;
	CountriesByIndustryDescendingMultiSet countries{HoI4::Country::compareCountriesByIndustryDescending};
	std::map<std::string, std::string> countryToRoleAssignments;
	std::string saveName;

	// Construct and emplace a role of each class
	void initialzeRoles(const std::set<std::string> possibleRoles);

	// For a given country, update all role fit values and sort container
	void recalculateRoleFits(const HoI4::Country& country);

	// Apply role to country, only if a valid match exists. Update tag -> Role assignments.
	void applyRole(std::shared_ptr<HoI4::Country> country);

	// Apply role to country, ignore all restrictions and collect possible resulting mod.
	void applyRole(std::shared_ptr<HoI4::Country> country, const std::shared_ptr<Role> role);


	const std::shared_ptr<Role> getRoleByName(const std::string roleName);
};

} // namespace HoI4

#endif // SCENARIO_CREATOR_H