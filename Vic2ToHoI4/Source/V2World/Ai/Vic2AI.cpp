#include "Vic2AI.h"
#include "AIStrategy.h"
#include "ParserHelpers.h"



Vic2::Vic2AI::Vic2AI(std::istream& theStream)
{
	registerRegex("conquer_prov|threat|antagonize|befriend|protect|rival",
		 [this](const std::string& strategyType, std::istream& theStream) {
			 const auto& strategy = AIStrategy(strategyType, theStream);
			 aiStrategies.push_back(strategy);
		 });
	registerRegex("[A-Za-z0-9_]+", commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}