#ifndef SCENARIO_BUILDER_H
#define SCENARIO_BUILDER_H

#include "Roles/Role.h"

class ScenarioBuilder
{
  public:
	explicit ScenarioBuilder(const std::map<std::string, std::shared_ptr<HoI4::Country>>& c);

  private:
	struct RoleComparator
	{
		bool operator()(const Role* lhs, const Role* rhs) { return Role::roleComparator(lhs, rhs); };
	};
	struct CountryComparator
	{
		bool operator()(const HoI4::Country* lhs, const HoI4::Country* rhs)
		{
			return lhs->getIndustry() < rhs->getIndustry();
		};
	};

	// Need to pick best type of ptr
	std::multiset<std::shared_ptr<Role>, RoleComparator> roles;
	std::multiset<std::shared_ptr<HoI4::Country>, CountryComparator> countries;
};
#endif // SCENARIO_BUILDER