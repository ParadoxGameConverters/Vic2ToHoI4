#include "AIFactory.h"
#include "ParserHelpers.h"



Vic2::AI::Factory::Factory()
{
	registerKeyword("conquer_prov", [this](const std::string& strategyType, std::istream& theStream) {
		ai->conquerStrategies.push_back(*aiStrategyFactory.importStrategy(strategyType, theStream));
	});
	registerRegex("threat|antagonize|befriend|protect|rival",
		 [this](const std::string& strategyType, std::istream& theStream) {
			 ai->aiStrategies.push_back(*aiStrategyFactory.importStrategy(strategyType, theStream));
		 });
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Vic2::AI> Vic2::AI::Factory::importAI(std::istream& theStream)
{
	ai = std::make_unique<AI>();
	parseStream(theStream);
	return std::move(ai);
}