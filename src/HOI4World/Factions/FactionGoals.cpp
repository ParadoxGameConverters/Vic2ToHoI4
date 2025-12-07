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


void HoI4::FactionGoals::updateFactionGoals(const std::set<std::string>& majorIdeologies)
{
	Log(LogLevel::Info) << "\tUpdating ideological faction goals";
	updateGuardiansOfPeaceGoal(majorIdeologies);
	for (const auto& ideology: majorIdeologies)
	{
		updateDefeatOfAntiIdeologyGoal(ideology, majorIdeologies);
		for (const auto& goal: importedGoals.at(ideology))
		{
			ideologicalGoals.push_back(goal);
		}
	}
}


void HoI4::FactionGoals::updateDefeatOfAntiIdeologyGoal(const std::string& ideology,
	 const std::set<std::string>& majorIdeologies)
{
	std::map<std::string, std::string> ideologyAdjMap;
	ideologyAdjMap.emplace("democratic", "democratic");
	ideologyAdjMap.emplace("communism", "communist");
	ideologyAdjMap.emplace("fascism", "fascist");
	ideologyAdjMap.emplace("radical", "radical");
	ideologyAdjMap.emplace("absolutist", "absolutist");
	ideologyAdjMap.emplace("neutrality", "unaligned");

	const auto& ideologyAdj = ideologyAdjMap.at(ideology);

	auto& goals = importedGoals.at(ideology);
	auto goalItr = std::find_if(goals.begin(), goals.end(), [ideologyAdj](const FactionGoal& a) {
		return a.getId() == "faction_goal_defeat_of_anti_" + ideologyAdj + "s";
	});
	if (goalItr == goals.end())
	{
		return;
	}

	std::set<std::string> antiIdeologies;
	for (const auto& antiIdeology: majorIdeologies)
	{
		if (antiIdeology != ideology && antiIdeology != "neutrality")
		{
			antiIdeologies.emplace(antiIdeology);
		}
	}

	std::string visibleStr = "= {\n";
	visibleStr += "\t\tcollection_size = {\n";
	visibleStr += "\t\t\tinput = {\n";
	visibleStr += "\t\t\t\tinput = game:scope\n";
	visibleStr += "\t\t\t\toperators = {\n";
	visibleStr += "\t\t\t\t\tfaction_members\n";
	visibleStr += "\t\t\t\t\tlimit = {\n";
	visibleStr += "\t\t\t\t\t\tOR = {\n";
	for (const auto& antiIdeology: antiIdeologies)
	{
		visibleStr += "\t\t\t\t\t\t\thas_government = " + antiIdeology + "\n";
	}
	visibleStr += "\t\t\t\t\t\t}\n";
	visibleStr += "\t\t\t\t\t}\n";
	visibleStr += "\t\t\t\t}\n";
	visibleStr += "\t\t\t\tname = FACTION\n";
	visibleStr += "\t\t\t}\n";
	visibleStr += "\t\t\tvalue < 1\n";
	visibleStr += "\t\t}\n";
	visibleStr += "\t}\n";
	goalItr->setVisible(visibleStr);

	std::string completedStr = "= {\n";
	completedStr += "\t\tcollection_size = {\n";
	completedStr += "\t\t\tinput = {\n";
	completedStr += "\t\t\t\tinput = collection:anti_" + ideologyAdj + "_controlled_states_my_continent\n";

	completedStr += "\t\t\t\tname = COLLECTION_STATES_MY_CONTINENT_CONTROLLED";
	for (const auto& antiIdeology: antiIdeologies)
	{
		std::string uppercaseAntiIdeologyAdj = ideologyAdjMap.at(antiIdeology);
		std::ranges::transform(uppercaseAntiIdeologyAdj, uppercaseAntiIdeologyAdj.begin(), ::toupper);
		completedStr += "_" + uppercaseAntiIdeologyAdj;
	}
	completedStr += "\n";

	completedStr += "\t\t\t}\n";
	completedStr += "\t\t\tvalue < 1\n";
	completedStr += "\t\t}\n";
	completedStr += "\t\t\n";
	completedStr += "\t}\n";
	goalItr->setCompleted(completedStr);

	std::string aiWillDoStr = "= {\n";
	aiWillDoStr += "\t\tbase = 0\n";
	aiWillDoStr += "\t\tmodifier = { \n";
	aiWillDoStr += "\t\t\tadd = 1 # If war with communists you probably hate them\n";
	aiWillDoStr += "\t\t\tany_enemy_country = {\n";
	aiWillDoStr += "\t\t\t\tOR = {\n";
	for (const auto& antiIdeology: antiIdeologies)
	{
		aiWillDoStr += "\t\t\t\t\thas_government = " + antiIdeology + "\n";
	}
	aiWillDoStr += "\t\t\t\t}\n";
	aiWillDoStr += "\t\t\t}\n";
	aiWillDoStr += "\t\t}\n";
	aiWillDoStr += "\t}\n";
	goalItr->setAiWillDo(aiWillDoStr);
}


void HoI4::FactionGoals::updateGuardiansOfPeaceGoal(const std::set<std::string>& majorIdeologies)
{
	auto& goals = importedGoals.at("neutrality");
	auto goalItr = std::find_if(goals.begin(), goals.end(), [](const FactionGoal& a) {
		return a.getId() == "faction_goal_guardians_of_peace";
	});
	if (goalItr == goals.end())
	{
		return;
	}

	std::string visibleStr = "= {\n";
	visibleStr += "\t\tdate < 1939.1.1\n";
	visibleStr += "\t\tFROM = {\n";
	for (const auto& ideology: majorIdeologies)
	{
		if (ideology == "neutrality" || ideology == "democratic")
		{
			continue;
		}
		visibleStr += "\t\t\tNOT = { has_government = " + ideology + " }\n";
	}
	visibleStr += "\t\t\tNOT = { has_country_flag = guardians_of_peace_been_at_war_flag }\n";
	visibleStr += "\t\t}\n";
	visibleStr += "\t}\n";
	goalItr->setVisible(visibleStr);

	std::string aiWillDoStr = "= {\n";
	aiWillDoStr += "\t\tbase = 0\n";
	if (majorIdeologies.contains("democratic"))
	{
		aiWillDoStr += "\t\tmodifier = {\n";
		aiWillDoStr += "\t\t\tadd = 1\n";
		aiWillDoStr += "\t\t\thas_government = democratic\n";
		aiWillDoStr += "\t\t}\n";
	}
	aiWillDoStr += "\t}\n";
	goalItr->setAiWillDo(aiWillDoStr);
}
