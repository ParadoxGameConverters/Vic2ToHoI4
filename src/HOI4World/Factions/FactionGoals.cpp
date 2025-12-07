#include "src/HOI4World/Factions/FactionGoals.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::FactionGoals::FactionGoals()
{
	Log(LogLevel::Info) << "\tImporting faction goals and manifests";

	registerRegex(commonItems::catchallRegex, [this](const std::string& ideology, std::istream& theStream) {
		const FactionGoals& ideologyGoals(theStream);
		for (const auto& goal: ideologyGoals.ideologicalGoals)
		{
			importedGoals[ideology].push_back(goal);
		}
	});
	parseFile(std::filesystem::path("Configurables") / "ideological_faction_goals.txt");
}


HoI4::FactionGoals::FactionGoals(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& id, std::istream& theStream) {
		ideologicalGoals.push_back(FactionGoal(id, theStream));
	});
	parseStream(theStream);
}