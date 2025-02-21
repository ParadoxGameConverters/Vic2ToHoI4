#include "src/V2World/Military/Leaders/LeaderFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Log.h"
#include "external/common_items/ParserHelpers.h"



Vic2::Leader::Factory::Factory(Traits&& traits_): traits(traits_)
{
	registerKeyword("name", [this](std::istream& theStream) {
		leader->name = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("type", [this](std::istream& theStream) {
		leader->type = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("prestige", [this](std::istream& theStream) {
		leader->prestige = commonItems::singleDouble{theStream}.getDouble();
	});
	registerRegex("personality|background", [this](const std::string& unused, std::istream& theStream) {
		for (const auto& effect: traits.getEffectsForTrait(commonItems::singleString{theStream}.getString()))
		{
			auto [effectIterator, inserted] = leader->traitEffects.insert(effect);
			if (!inserted)
			{
				effectIterator->second += effect.second;
			}
		}
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Vic2::Leader> Vic2::Leader::Factory::getLeader(std::istream& theStream)
{
	leader = std::make_unique<Leader>();
	parseStream(theStream);
	return std::move(leader);
}