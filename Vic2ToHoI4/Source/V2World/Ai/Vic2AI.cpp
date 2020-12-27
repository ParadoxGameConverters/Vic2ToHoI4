#include "Vic2AI.h"
#include "AIStrategy.h"
#include "AIStrategyFactory.h"
#include "ParserHelpers.h"
#include "V2World/Provinces/Province.h"
#include "V2World/World/World.h"



Vic2::Vic2AI::Vic2AI(std::istream& theStream)
{
	AIStrategy::Factory aiStrategyFactory;

	registerRegex("threat|antagonize|befriend|protect|rival",
		 [this, &aiStrategyFactory](const std::string& strategyType, std::istream& theStream) {
			 const auto& strategy = aiStrategyFactory.importStrategy(strategyType, theStream);
			 aiStrategies.push_back(*strategy);
		 });
	registerKeyword("conquer_prov",
		 [this, &aiStrategyFactory](const std::string& strategyType, std::istream& theStream) {
			 const auto& conquerStrategy = aiStrategyFactory.importStrategy(strategyType, theStream);
			 conquerStrategies.push_back(*conquerStrategy);
		 });
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}


void Vic2::Vic2AI::consolidateConquerStrategies(const std::map<int, std::shared_ptr<Province>>& provinces)
{
	for (const auto& strategy: conquerStrategies)
	{
		if (const auto& provinceItr = provinces.find(strategy.getProvID()); provinceItr != provinces.end())
		{
			const auto& province = provinceItr->second;
			if (!province)
			{
				continue;
			}

			const auto& owner = province->getOwner();
			if (const auto& conquerTag = consolidatedConquerStrategies.find(owner);
				 conquerTag == consolidatedConquerStrategies.end())
			{
				consolidatedConquerStrategies.insert(make_pair(owner, strategy.getValue()));
			}
			else
			{
				updateStrategy(owner, strategy.getValue());
			}
		}
	}
}


void Vic2::Vic2AI::updateStrategy(const std::string& tag, int valueToAdd)
{
	consolidatedConquerStrategies.find(tag)->second += valueToAdd;
}