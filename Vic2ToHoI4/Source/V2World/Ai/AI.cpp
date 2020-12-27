#include "AI.h"



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
		const auto& value = strategy.getValue();

		auto [existingStrategy, inserted] = consolidatedConquerStrategies.insert(make_pair(owner, value));
		if (!inserted)
		{
			existingStrategy->second += value;
		}
	}
}