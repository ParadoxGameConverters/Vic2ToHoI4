#include "CasusBelliFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"
using commonItems::getString;



Mappers::CasusBelliFactory::CasusBelliFactory()
{
	registerKeyword("vic", [this](std::istream& theStream) {
		cbs_.insert(getString(theStream));
	});
	registerKeyword("hoi", [this](std::istream& theStream) {
		warGoal_ = getString(theStream);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


Mappers::CasusBelli Mappers::CasusBelliFactory::importCasusBelli(std::istream& theStream)
{
	cbs_.clear();
	warGoal_.clear();
	parseStream(theStream);
	return CasusBelli(cbs_, warGoal_);
}