#include "src/OutHoi4/Scorers/OutScorers.h"
#include <fstream>



const std::map<std::string, std::string> ideologyNameMap = {{"fascism", "fascist"},
	 {"communism", "communist"},
	 {"democratic", "democratic"},
	 {"neutrality", "non_aligned"},
	 {"absolutist", "absolutist"},
	 {"radical", "radical"}};


void outputMajorScorers(const std::set<std::string>& majorIdeologies, std::ostream& output)
{
	for (const auto& ideology: majorIdeologies)
	{
		output << ideologyNameMap.at(ideology) << "_major_scorer = { #Finds biggest " << ideologyNameMap.at(ideology)
				 << "\n";
		output << "\t# Valid example of mission scorer:\n";
		output << "\ttargets = {\n";
		output << "\t\t# describe the target to consider\n";
		output << "\t\ttargets_dynamic = no\n";
		output << "\t\ttarget_non_existing = no\n";
		output << "\t\t#target_array = global.majors\n";
		output << "\t\ttarget_array = global.countries\n";
		output << "\t\t# MTTH like score description\n";
		output << "\t\t# THIS is a target\n";
		output << "\t\t# FROM is the initiator\n";
		output << "\t\tscore = {\n";
		output << "\t\t\tbase = 1\n";
		output << "\t\t\t# Add tension added by country\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\talways = yes \n";
		output << "\t\t\t\tadd = has_added_tension_amount\n";
		output << "\t\t\t}\t\t\n";
		output << "\t\t\t# Add total number of Divisions \n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\talways = yes \n";
		output << "\t\t\t\tadd = num_armies\n";
		output << "\t\t\t}\n";
		output << "\t\t\t# add factories\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\talways = yes \n";
		output << "\t\t\t\tadd = num_of_factories\n";
		output << "\t\t\t}\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\tis_major = yes\n";
		output << "\t\t\t\tadd = 100\n";
		output << "\t\t\t}\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\tis_faction_leader = yes \n";
		output << "\t\t\t\tadd = 50\n";
		output << "\t\t\t}\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\tNOT = { has_government = " << ideology << " }\n";
		output << "\t\t\t\tfactor = 0 \n";
		output << "\t\t\t}\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\texists = no \n";
		output << "\t\t\t\tfactor = 0\n";
		output << "\t\t\t}\n";
		output << "\t\t}\n";
		output << "\t}\n";
		output << "}\n";
		output << "\n";
	}
}

void outputSecondaryScorers(const std::set<std::string>& majorIdeologies, std::ostream& output)
{
	if (majorIdeologies.contains("fascism"))
	{
		output << "local_fascist_country = {\n";
		output << "\t# Valid example of mission scorer:\n";
		output << "\ttargets = {\n";
		output << "\t\t# describe the target to consider\n";
		output << "\t\ttargets_dynamic = no\n";
		output << "\t\ttarget_non_existing = no\n";
		output << "\t\t#target_array = global.majors\n";
		output << "\t\ttarget_array = global.countries\n";
		output << "\t\t# MTTH like score description\n";
		output << "\t\t# THIS is a target\n";
		output << "\t\t# FROM is the initiator\n";
		output << "\t\tscore = {\n";
		output << "\t\t\tbase = 1\n";
		output << "\t\t\t\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\tis_major = yes\n";
		output << "\t\t\t\tfactor = 10\n";
		output << "\t\t\t}\n";
		output << "\t\t\t# Add tension added by country\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\talways = yes \n";
		output << "\t\t\t\tadd = has_added_tension_amount\n";
		output << "\t\t\t}\n";
		output << "\t\t\t# Add total number of Divisions \n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\talways = yes\n";
		output << "\t\t\t\tadd = num_armies \n";
		output << "\t\t\t}\n";
		output << "\t\t\t# If neighbor, more scary\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\tis_neighbor_of = FROM\n";
		output << "\t\t\t\tfactor = 2\n";
		output << "\t\t\t}\n";
		output << "\t\t\t# Same continent also more scary\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\tOR = {\n";
		output << "\t\t\t\t\tAND = {\n";
		output << "\t\t\t\t\t\tTHIS.capital_scope = { is_on_continent = europe }\n";
		output << "\t\t\t\t\t\tFROM.capital_scope = { is_on_continent = europe }\n";
		output << "\t\t\t\t\t}\n";
		output << "\t\t\t\t\tAND = {\n";
		output << "\t\t\t\t\t\tTHIS.capital_scope = { is_on_continent = asia }\n";
		output << "\t\t\t\t\t\tFROM.capital_scope = { is_on_continent = asia }\n";
		output << "\t\t\t\t\t}\n";
		output << "\t\t\t\t\tAND = {\n";
		output << "\t\t\t\t\t\tOR = {\n";
		output << "\t\t\t\t\t\t\tTHIS.capital_scope = { is_on_continent = north_america }\n";
		output << "\t\t\t\t\t\t\tTHIS.capital_scope = { is_on_continent = south_america }\n";
		output << "\t\t\t\t\t\t}\n";
		output << "\t\t\t\t\t\tOR = {\n";
		output << "\t\t\t\t\t\t\tFROM.capital_scope = { is_on_continent = north_america }\n";
		output << "\t\t\t\t\t\t\tFROM.capital_scope = { is_on_continent = south_america }\n";
		output << "\t\t\t\t\t\t}\n";
		output << "\t\t\t\t\t}\n";
		output << "\t\t\t\t\tAND = {\n";
		output << "\t\t\t\t\t\tTHIS.capital_scope = { is_on_continent = africa }\n";
		output << "\t\t\t\t\t\tFROM.capital_scope = { is_on_continent = africa }\n";
		output << "\t\t\t\t\t}\n";
		output << "\t\t\t\t\tAND = {\n";
		output << "\t\t\t\t\t\tTHIS.capital_scope = { is_on_continent = middle_east }\n";
		output << "\t\t\t\t\t\tFROM.capital_scope = { is_on_continent = middle_east }\n";
		output << "\t\t\t\t\t}\n";
		output << "\t\t\t\t\tAND = {\n";
		output << "\t\t\t\t\t\tOR = {\n";
		output << "\t\t\t\t\t\t\tTHIS.capital_scope = { is_on_continent = australia }\n";
		output << "\t\t\t\t\t\t\tTHIS.capital_scope = { is_on_continent = asia }\n";
		output << "\t\t\t\t\t\t}\n";
		output << "\t\t\t\t\t\tFROM.capital_scope = { is_on_continent = australia }\n";
		output << "\t\t\t\t\t}\t\n";
		output << "\t\t\t\t}\n";
		output << "\t\t\t\tfactor = 3\n";
		output << "\t\t\t}\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\tadd = num_armies\n";
		output << "\t\t\t}\n";
		output << "\t\t\t# add factories\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\talways = yes \n";
		output << "\t\t\t\tadd = num_of_factories\n";
		output << "\t\t\t}\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\tNOT = { has_government = fascism }\n";
		output << "\t\t\t\tfactor = 0 \n";
		output << "\t\t\t}\n";
		output << "\t\t}\n";
		output << "\t}\n";
		output << "}\n";
		output << "\n";
		output << "fascist_bully_scorer = { #Finds meanest fascist\n";
		output << "\t# Valid example of mission scorer:\n";
		output << "\ttargets = {\n";
		output << "\t\t# describe the target to consider\n";
		output << "\t\ttargets_dynamic = no\n";
		output << "\t\ttarget_non_existing = no\n";
		output << "\t\t#target_array = global.majors\n";
		output << "\t\ttarget_array = global.countries\n";
		output << "\t\t# MTTH like score description\n";
		output << "\t\t# THIS is a target\n";
		output << "\t\t# FROM is the initiator\n";
		output << "\t\tscore = {\n";
		output << "\t\t\tbase = 1\n";
		output << "\t\t\t# Add tension added by country\n";
		output << "\t\t\t# Add total number of Divisions \n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\talways = yes \n";
		output << "\t\t\t\tadd = num_armies\n";
		output << "\t\t\t}\n";
		output << "\t\t\t# add factories\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\talways = yes \n";
		output << "\t\t\t\tadd = num_of_factories\n";
		output << "\t\t\t}\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\talways = yes \n";
		output << "\t\t\t\tadd = has_added_tension_amount\n";
		output << "\t\t\t}\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\tis_major = yes\n";
		output << "\t\t\t\tadd = 100\n";
		output << "\t\t\t}\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\tis_faction_leader = yes \n";
		output << "\t\t\t\tadd = 100\n";
		output << "\t\t\t}\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\tNOT = { has_government = fascism }\n";
		output << "\t\t\t\tfactor = 0 \n";
		output << "\t\t\t}\n";
		output << "\t\t}\n";
		output << "\t}\n";
		output << "}\n";
		output << "\n";
	}

	if (majorIdeologies.contains("democratic"))
	{
		output << "democratic_faction_leader_scorer = { # Finds biggest Democratic Nation\n";
		output << "\ttargets = {\n";
		output << "\t\t# describe the target to consider\n";
		output << "\t\ttargets_dynamic = no\n";
		output << "\t\ttarget_non_existing = no\n";
		output << "\t\t#target_array = global.majors\n";
		output << "\t\ttarget_array = global.countries\n";
		output << "\t\t# MTTH like score description\n";
		output << "\t\t# THIS is a target\n";
		output << "\t\t# FROM is the initiator\n";
		output << "\t\tscore = {\n";
		output << "\t\t\tbase = 1\n";
		output << "\t\t\t# Add tension added by country\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\talways = yes \n";
		output << "\t\t\t\tadd = has_added_tension_amount\n";
		output << "\t\t\t}\t\t\n";
		output << "\t\t\t# Add total number of Divisions \n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\talways = yes \n";
		output << "\t\t\t\tadd = num_armies\n";
		output << "\t\t\t}\n";
		output << "\t\t\t# add factories\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\talways = yes \n";
		output << "\t\t\t\tadd = num_of_factories\n";
		output << "\t\t\t}\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\tis_major = yes\n";
		output << "\t\t\t\tadd = 100\n";
		output << "\t\t\t}\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\tis_faction_leader = no \n";
		output << "\t\t\t\tfactor = 0.1\n";
		output << "\t\t\t}\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\tNOT = { has_government = democratic }\n";
		output << "\t\t\t\tfactor = 0 \n";
		output << "\t\t\t}\n";
		output << "\t\t}\n";
		output << "\t}\n";
		output << "}\n";
		output << "\n";
		output << "democratic_sleeping_giant_scorer = { #Finds the least armed big democratic country. \n";
		output << " \ttargets = {\n";
		output << "\t\t# describe the target to consider\n";
		output << "\t\ttargets_dynamic = no\n";
		output << "\t\ttarget_non_existing = no\n";
		output << "\t\t#target_array = global.majors\n";
		output << "\t\ttarget_array = global.countries\n";
		output << "\t\t# MTTH like score description\n";
		output << "\t\t# THIS is a target\n";
		output << "\t\t# FROM is the initiator\n";
		output << "\t\tscore = {\n";
		output << "\t\t\tbase = 1\n";
		output << "\t\t\t# Add tension added by country\n";
		output << "\t\t\t# Add total number of Divisions \n";
		output << "\t\t\t# add factories\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\talways = yes \n";
		output << "\t\t\t\tadd = num_of_factories\n";
		output << "\t\t\t}\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\talways = yes \n";
		output << "\t\t\t\tadd = -num_armies\n";
		output << "\t\t\t}\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\talways = yes \n";
		output << "\t\t\t\tadd = -has_added_tension_amount\n";
		output << "\t\t\t}\t\t\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\tis_major = yes\n";
		output << "\t\t\t\tadd = 30\n";
		output << "\t\t\t}\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\tis_faction_leader = yes \n";
		output << "\t\t\t\tfactor = 0.5\n";
		output << "\t\t\t}\n";
		output << "\t\t\tmodifier = {\n";
		output << "\t\t\t\tNOT = { has_government = democratic }\n";
		output << "\t\t\t\tfactor = 0 \n";
		output << "\t\t\t}\n";
		output << "\t\t}\n";
		output << "\t}   \n";
		output << "}\n";
		output << "\n";
	}
}

void outputMajorScorersByContinent(const std::set<std::string>& majorIdeologies, std::ostream& output)
{
	const std::map<std::string, std::string> continentAdjMap = {{"europe", "european"},
		 {"asia", "asian"},
		 {"america", "american"},
		 {"africa", "african"}};

	for (const auto& [continent, adjective]: continentAdjMap)
	{
		for (const auto& ideology: majorIdeologies)
		{
			output << adjective << "_" << ideologyNameMap.at(ideology) << "_major_scorer = { #Finds biggest "
					 << ideologyNameMap.at(ideology) << " in " << continent << "\n";
			output << "\t# Valid example of mission scorer:\n";
			output << "\ttargets = {\n";
			output << "\t\t# describe the target to consider\n";
			output << "\t\ttargets_dynamic = no\n";
			output << "\t\ttarget_non_existing = no\n";
			output << "\t\t#target_array = global.majors\n";
			output << "\t\ttarget_array = global.countries\n";
			output << "\t\t# MTTH like score description\n";
			output << "\t\t# THIS is a target\n";
			output << "\t\t# FROM is the initiator\n";
			output << "\t\tscore = {\n";
			output << "\t\t\tbase = 1\n";
			output << "\t\t\t# Add tension added by country\n";
			output << "\t\t\tmodifier = {\n";
			output << "\t\t\t\talways = yes \n";
			output << "\t\t\t\tadd = has_added_tension_amount\n";
			output << "\t\t\t}\t\t\n";
			output << "\t\t\t# Add total number of Divisions \n";
			output << "\t\t\tmodifier = {\n";
			output << "\t\t\t\talways = yes \n";
			output << "\t\t\t\tadd = num_armies\n";
			output << "\t\t\t}\n";
			output << "\t\t\t# add factories\n";
			output << "\t\t\tmodifier = {\n";
			output << "\t\t\t\talways = yes \n";
			output << "\t\t\t\tadd = num_of_factories\n";
			output << "\t\t\t}\n";
			output << "\t\t\tmodifier = {\n";
			output << "\t\t\t\tis_major = yes\n";
			output << "\t\t\t\tadd = 100\n";
			output << "\t\t\t}\n";
			output << "\t\t\tmodifier = {\n";
			output << "\t\t\t\tis_faction_leader = yes \n";
			output << "\t\t\t\tadd = 50\n";
			output << "\t\t\t}\n";
			output << "\t\t\tmodifier = {\n";
			output << "\t\t\t\tNOT = { has_government = " << ideology << " }\n";
			output << "\t\t\t\tfactor = 0 \n";
			output << "\t\t\t}\n";

			if (continent == "america")
			{
				output << "\t\t\tmodifier = {\n";
				output << "\t\t\t\tOR = { \n";
				output << "\t\t\t\t\tNOT = { THIS.capital_scope = { is_on_continent = south_america } } \n";
				output << "\t\t\t\t\tNOT = { THIS.capital_scope = { is_on_continent = north_america } }\n";
				output << "\t\t\t\t}\n";
				output << "\t\t\t\tfactor = 0 \n";
				output << "\t\t\t}\n";
			}
			else if (continent == "asia" || continent == "australia" || continent == "middle_east")
			{
				output << "\t\t\tmodifier = {\n";
				output << "\t\t\t\tOR = { \n";
				output << "\t\t\t\t\tNOT = { THIS.capital_scope = { is_on_continent = asia } } \n";
				output << "\t\t\t\t\tNOT = { THIS.capital_scope = { is_on_continent = australia } }\n";
				output << "\t\t\t\t\tNOT = { THIS.capital_scope = { is_on_continent = middle_east } }\n";
				output << "\t\t\t\t}\n";
				output << "\t\t\t\tfactor = 0 \n";
				output << "\t\t\t}\n";
			}
			else
			{
				output << "\t\t\tmodifier = {\n";
				output << "\t\t\t\tNOT = { THIS.capital_scope = { is_on_continent = " << continent << " } }\n";
				output << "\t\t\t\tfactor = 0 \n";
				output << "\t\t\t}\n";
			}

			output << "\t\t}\n";
			output << "\t}\n";
			output << "}\n";
			output << "\n";
		}
	}
}


void HoI4::outputScorers(const std::set<std::string>& majorIdeologies, const std::string& outputName)
{
	std::ofstream scorersFile("output/" + outputName + "/common/scorers/country/generic_platonic_scorers.txt",
		 std::ios::app);
	if (!scorersFile.is_open())
	{
		throw std::runtime_error(
			 "Could not open output/" + outputName + "/common/scorers/country/generic_platonic_scorers.txt");
	}

	outputMajorScorers(majorIdeologies, scorersFile);
	outputSecondaryScorers(majorIdeologies, scorersFile);
	outputMajorScorersByContinent(majorIdeologies, scorersFile);

	scorersFile.close();
}