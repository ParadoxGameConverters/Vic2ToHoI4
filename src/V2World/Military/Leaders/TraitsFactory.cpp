#include "src/V2World/Military/Leaders/TraitsFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "src/V2World/Military/Leaders/TraitGroup.h"



Vic2::Traits::Factory::Factory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& unused, std::istream& theStream) {
		TraitGroup group(theStream);
		for (const auto& trait: group.takeTraits())
		{
			traits->traits.insert(trait);
		}
	});
}


std::unique_ptr<Vic2::Traits> Vic2::Traits::Factory::loadTraits(const std::string& Vic2Location)
{
	traits = std::make_unique<Traits>();
	parseFile(Vic2Location + "/common/traits.txt");
	return std::move(traits);
}