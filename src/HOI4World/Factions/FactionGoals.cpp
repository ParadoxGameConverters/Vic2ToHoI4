#include "src/HOI4World/Factions/FactionGoals.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ConvenientParser.h"



HoI4::FactionGoals::FactionGoals(const std::set<std::string>& majorIdeologies)
{
	importFactionGoals(std::filesystem::path("Configurables") / "ideological_faction_goals.txt");
}


void HoI4::FactionGoals::importFactionGoals(const std::filesystem::path& fileName)
{
	Log(LogLevel::Info) << "\tImporting faction goals and manifests";

	registerRegex(commonItems::catchallRegex, [this](const std::string& id, std::istream& theStream) {
		importedGoals.emplace(id, std::make_shared<FactionGoal>(id, theStream));
	});
	parseFile(fileName);
}