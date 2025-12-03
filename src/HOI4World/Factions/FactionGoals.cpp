#include "src/HOI4World/Factions/FactionGoals.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ConvenientParser.h"



void HoI4::FactionGoals::importFactionGoals(const std::filesystem::path& fileName)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& id, std::istream& theStream) {
		factionGoals.emplace(id, std::make_shared<FactionGoal>(id, theStream));
	});
	parseFile(fileName);
}