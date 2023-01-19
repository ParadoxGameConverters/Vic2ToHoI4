#include "src/V2World/World/World.h"
#include "src/Configuration.h"
#include "src/V2World/Provinces/Province.h"
#include <ranges>



std::optional<const std::shared_ptr<Vic2::Province>> Vic2::World::getProvince(const int provNum) const
{
	const auto provinceItr = provinces.find(provNum);
	if (provinceItr == provinces.end())
	{
		return std::nullopt;
	}

	return provinceItr->second;
}


std::vector<std::reference_wrapper<const Vic2::State>> Vic2::World::getStates() const
{
	std::vector<std::reference_wrapper<const State>> states;
	for (const auto& country: countries | std::views::values)
	{
		for (const State& state: country.getStates())
		{
			states.emplace_back(std::reference_wrapper(state));
		}
	}

	return states;
}