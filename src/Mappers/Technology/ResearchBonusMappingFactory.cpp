#include "ResearchBonusMappingFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



Mappers::ResearchBonusMapping::Factory::Factory()
{
	registerKeyword("vic2", [this](std::istream& theStream) {
		researchBonusMapping->vic2Requirements.insert(commonItems::getString(theStream));
	});
	registerRegex(commonItems::catchallRegex, [this](const std::string& valueName, std::istream& theStream) {
		researchBonusMapping->researchBonuses.insert(
			 std::make_pair(valueName, static_cast<float>(commonItems::getDouble(theStream))));
	});
}


std::unique_ptr<Mappers::ResearchBonusMapping> Mappers::ResearchBonusMapping::Factory::importResearchBonusMapping(
	 std::istream& theStream)
{
	researchBonusMapping = std::make_unique<ResearchBonusMapping>();
	parseStream(theStream);
	return std::move(researchBonusMapping);
}