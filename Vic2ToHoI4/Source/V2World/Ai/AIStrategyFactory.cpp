#include "AIStrategyFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



Vic2::AIStrategy::Factory::Factory()
{
	registerKeyword("id", [this](std::istream& theStream) {
		if (aiStrategy->type == "conquer_prov")
		{
			aiStrategy->provID = commonItems::singleInt{theStream}.getInt();
		}
		else
		{
			aiStrategy->id = commonItems::singleString{theStream}.getString();
		}
	});
	registerKeyword("value", [this](std::istream& theStream) {
		aiStrategy->value = commonItems::singleInt{theStream}.getInt();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Vic2::AIStrategy> Vic2::AIStrategy::Factory::importStrategy(const std::string& strategyType,
	 std::istream& theStream)
{
	aiStrategy = std::make_unique<AIStrategy>();
	aiStrategy->type = strategyType;
	parseStream(theStream);
	return std::move(aiStrategy);
}