#include "src/HOI4World/Scorers/ScorerFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::Scorer::Factory::Factory()
{
	registerKeyword("targets", [this](std::istream& theStream) {
		scorer->setTargets(commonItems::stringOfItem(theStream).getString());
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<HoI4::Scorer> HoI4::Scorer::Factory::getScorer(const std::string& name, std::istream& theStream)
{
	scorer = std::make_unique<Scorer>();
	scorer->setName(name);

	parseStream(theStream);

	return std::move(scorer);
}