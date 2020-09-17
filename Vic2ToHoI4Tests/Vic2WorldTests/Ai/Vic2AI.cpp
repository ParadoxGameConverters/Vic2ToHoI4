#include "../Vic2ToHoI4/Source/V2World/Ai/Vic2AI.h"
#include "../Vic2ToHoI4/Source/V2World/Ai/AIStrategy.h"
#include "../Vic2ToHoI4/Source/V2World/World.h"
#include "../Vic2ToHoI4/Source/V2World/Provinces/Province.h"
#include "ParserHelpers.h"



Vic2::Vic2AI::Vic2AI(std::istream& theStream)
{
	registerRegex("threat|antagonize|befriend|protect|rival",
		 [this](const std::string& strategyType, std::istream& theStream) {
			 const auto& strategy = AIStrategy(strategyType, theStream);
			 aiStrategies.push_back(strategy);
		 });
	registerRegex("conquer_prov", [this](const std::string& strategyType, std::istream& theStream) {
		const auto& conquerStrategy = AIStrategy(strategyType, theStream);
		conquerStrategies.push_back(conquerStrategy);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}

void Vic2::Vic2AI::consolidateConquerStrategies(const std::map<int, std::shared_ptr<Province>>& provinces)
{
	for (const auto& strategy: getConquerStrategies())
	{
		if (const auto& theProvince = provinces.find(strategy.getProvID())->second; theProvince)
		{
			const auto& owner = theProvince->getOwner();
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
	auto& value = consolidatedConquerStrategies.find(tag)->second;
	value += valueToAdd;
}