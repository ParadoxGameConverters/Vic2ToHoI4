#include "src/HOI4World/Scorers/ScorersFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/Scorers/ScorerFactory.h"



std::unique_ptr<HoI4::Scorers> HoI4::Scorers::Factory::getScorers()
{
	auto scorers = std::make_unique<Scorers>();
	Scorer::Factory scorerFactory;

	registerRegex(commonItems::catchallRegex,
		 [&scorers, &scorerFactory](const std::string& name, std::istream& theStream) {
			 const auto scorer = scorerFactory.getScorer(name, theStream);
			 scorers->giveScorer(std::move(*scorer));
		 });

	parseFile("Configurables/Scorers/generic_platonic_scorers.txt");
	return scorers;
}