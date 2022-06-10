#include "src/HOI4World/ScenarioBuilder/ScenarioBuilder.h"
#include "src/HOI4World/ScenarioBuilder/Roles/RoleArsenalOfIdeology.h"
#include "src/HOI4World/ScenarioBuilder/Roles/RoleSpanishCivilWar.h"
#include <ranges>

ScenarioBuilder::ScenarioBuilder(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countryMap)
{
	for (const auto& country: countryMap | std::views::values)
	{
		// NOTE: Could maybe use countries as a multiset here, but might not want to later
		auto position = std::lower_bound(countries.begin(),
			 countries.end(),
			 country->getIndustry(),
			 HoI4::Country::compareCountriesByIndustry);
		countries.insert(position, country);
	}

	roles.push_back(std::make_shared<RoleSpanishCivilWar>());
	roles.push_back(std::make_shared<RoleArsenalOfIdeology>());
}
