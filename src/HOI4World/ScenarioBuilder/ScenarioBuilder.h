#ifndef SCENARIO_BUILDER_H
#define SCENARIO_BUILDER_H

#include "src/HOI4World/ScenarioBuilder/Roles/Role.h"

namespace HoI4
{

class ScenarioBuilder
{
  public:
	class ConfigParser;

	ScenarioBuilder() = default;
	explicit ScenarioBuilder(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countryMap,
		 const std::string fileName = "dude");

	typedef std::multiset<std::shared_ptr<HoI4::Country>, decltype(&HoI4::Country::compareCountriesByIndustry)>
		 CountriesByIndustryMultiSet;

	[[nodiscard]] std::vector<std::shared_ptr<Role>> getRoles() const { return roles; };
	[[nodiscard]] CountriesByIndustryMultiSet getCountries() const { return countries; };


  private:
	// NOTE: does more than one ptr to each obj need to exist at a time? could unique_ptr work?
	std::vector<std::shared_ptr<Role>> roles;
	CountriesByIndustryMultiSet countries;

	// Construct and emplace a role of each class
	void initialzeRoles();
	// For a given country, update all role fit values and sort container
	void recalculateRoleFits(const HoI4::Country& country);
	// Apply role to country, no change to country if no valid match exists.
	void applyRole(const HoI4::Country& country);

	// TODO: config file and pre-gen file I/O
};

} // namespace HoI4

#endif // SCENARIO_BUILDER