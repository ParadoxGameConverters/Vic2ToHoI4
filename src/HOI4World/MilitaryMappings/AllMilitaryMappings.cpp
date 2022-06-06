#include "AllMilitaryMappings.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "external/common_items/StringUtils.h"
#include <fstream>



HoI4::allMilitaryMappings::allMilitaryMappings(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& mod, std::istream& theStream) {
		const auto newMod = commonItems::remQuotes(mod);
		militaryMappings newMappings(newMod, theStream);
		theMappings.insert(std::make_pair(newMod, std::move(newMappings)));
	});

	parseStream(theStream);
}


const HoI4::militaryMappings& HoI4::allMilitaryMappings::getMilitaryMappings(const Mods& Vic2Mods) const
{
	for (const auto& mod: Vic2Mods)
	{
		auto mapping = theMappings.find(mod.name);
		if (mapping != theMappings.end())
		{
			return mapping->second;
		}
	}

	return theMappings.at("default");
}