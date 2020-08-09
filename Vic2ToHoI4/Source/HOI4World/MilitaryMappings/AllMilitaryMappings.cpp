#include "AllMilitaryMappings.h"
#include "../../../../Fronter/commonItems/StringUtils.h"
#include "ParserHelpers.h"
#include <fstream>



HoI4::allMilitaryMappings::allMilitaryMappings(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& mod, std::istream& theStream) {
		militaryMappings newMappings(mod, theStream);
		theMappings.insert(std::make_pair(mod, std::move(newMappings)));
	});
	registerRegex(R"(\"[^\n^=^\{^\}^\"]+\")", [this](const std::string& mod, std::istream& theStream) {
		const auto newMod = stringutils::remQuotes(mod);
		militaryMappings newMappings(newMod, theStream);
		theMappings.insert(std::make_pair(newMod, std::move(newMappings)));
	});

	parseStream(theStream);
}


const HoI4::militaryMappings& HoI4::allMilitaryMappings::getMilitaryMappings(
	 const std::vector<Vic2::Mod>& Vic2Mods) const
{
	for (const auto& mod: Vic2Mods)
	{
		auto mapping = theMappings.find(mod.getName());
		if (mapping != theMappings.end())
		{
			return mapping->second;
		}
	}

	return theMappings.at("default");
}