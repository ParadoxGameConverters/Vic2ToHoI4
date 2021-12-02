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
		// value, provinces
		const auto& data = std::make_pair(strategy.getValue(), std::vector{strategy.getProvID()});

		auto [existingStrategy, inserted] = consolidatedConquerStrategies.insert(make_pair(owner, data));
		if (!inserted)
		{
			existingStrategy->second.first += strategy.getValue();
			existingStrategy->second.second.push_back(strategy.getProvID());
		}
	}
}