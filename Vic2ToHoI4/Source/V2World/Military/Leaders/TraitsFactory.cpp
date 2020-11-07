#include "TraitsFactory.h"
#include "ParserHelpers.h"
#include "TraitGroup.h"



Vic2::Traits::Factory::Factory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& unused, std::istream& theStream) {
		for (const auto& trait: TraitGroup{theStream}.takeTraits())
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