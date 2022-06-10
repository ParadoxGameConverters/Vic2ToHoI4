#include "src/HOI4World/ScenarioBuilder/ScenarioBuilder.h"
#include "src/HOI4World/ScenarioBuilder/Roles/RoleArsenalOfIdeology.h"
#include "src/HOI4World/ScenarioBuilder/Roles/RoleSpanishCivilWar.h"
#include <ranges>

ScenarioBuilder::ScenarioBuilder(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countryMap)
{
	for (const auto& country: countryMap | std::views::values)
	{
		countries.emplace(country);
	}

	roles.emplace(RoleSpanishCivilWar());
	roles.emplace(RoleArsenalOfIdeology());
}
