#include "AI.h"
#include "Log.h"
#include <ranges>



void Vic2::AI::consolidateConquerStrategies(const std::map<int, std::shared_ptr<Province>>& provinces)
{
	for (const auto& strategy: conquerStrategies)
	{
		const auto& provinceItr = provinces.find(strategy.getProvID());
		if (provinceItr == provinces.end())
		{
			continue;
		}
		const auto& province = provinceItr->second;
		if (!province)
		{
			continue;
		}

		const auto& owner = province->getOwner();
		const StrategyData data{.value = strategy.getValue(), .provinces = std::vector{strategy.getProvID()}};

		auto [existingStrategy, inserted] = consolidatedConquerStrategies.insert(make_pair(owner, data));
		if (!inserted)
		{
			existingStrategy->second.value += strategy.getValue();
			existingStrategy->second.provinces.push_back(strategy.getProvID());
		}
	}
}