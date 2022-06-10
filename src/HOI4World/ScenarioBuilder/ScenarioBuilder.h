#ifndef SCENARIO_BUILDER_H
#define SCENARIO_BUILDER_H

#include "src/HOI4World/ScenarioBuilder/Roles/Role.h"

class ScenarioBuilder
{
  public:
	explicit ScenarioBuilder(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countryMap);

  private:
	std::vector<std::shared_ptr<Role>> roles;
	std::multiset<std::shared_ptr<HoI4::Country>, decltype(&HoI4::Country::compareCountriesByIndustry)> countries;
};
#endif // SCENARIO_BUILDER