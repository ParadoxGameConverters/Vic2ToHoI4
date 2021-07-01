#include "CasusBellisFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



Mappers::CasusBellisFactory::CasusBellisFactory()
{
	registerKeyword("link", [this](std::istream& theStream) {
		for (const auto casusBelli = casusBelliFactory.importCasusBelli(theStream); const auto& cb: casusBelli.cbs_)
		{
			mappings.emplace(cb, casusBelli.warGoal_);
		}
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Mappers::CasusBellis> Mappers::CasusBellisFactory::importCasusBellis()
{
	mappings.clear();
	parseFile("Configurables/casus_bellis_mappings.txt");
	return std::make_unique<CasusBellis>(mappings);
}