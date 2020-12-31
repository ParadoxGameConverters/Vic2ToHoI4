#include "TraitGroup.h"
#include "CommonRegexes.h"
#include "Trait.h"



Vic2::TraitGroup::TraitGroup(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& traitName, std::istream& theStream) {
		auto effects = getTraitEffects(theStream);
		traits.insert(std::make_pair(traitName, effects));
	});
	parseStream(theStream);
}