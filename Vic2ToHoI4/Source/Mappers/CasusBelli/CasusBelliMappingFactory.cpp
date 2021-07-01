#include "CasusBelliMappingFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"
using commonItems::getString;



Mappers::CasusBelliMappingFactory::CasusBelliMappingFactory()
{
	registerKeyword("vic", [this](std::istream& theStream) {
		cbs_.insert(getString(theStream));
	});
	registerKeyword("hoi", [this](std::istream& theStream) {
		warGoal_ = getString(theStream);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


Mappers::CasusBelliMapping Mappers::CasusBelliMappingFactory::importCasusBelli(std::istream& theStream)
{
	cbs_.clear();
	warGoal_.clear();
	parseStream(theStream);
	return CasusBelliMapping{.cbs_ = cbs_, .warGoal_ = warGoal_};
}