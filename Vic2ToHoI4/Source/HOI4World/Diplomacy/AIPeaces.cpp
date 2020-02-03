#include "AIPeaces.h"
#include "../../Configuration.h"
#include <fstream>



HoI4::AIPeaces::AIPeaces() noexcept
{
	registerKeyword(std::regex("[A-Za-z0-9\\_]+"), [this](const std::string& peaceName, std::istream& theStream)
	{
		thePeaces.push_back(AIPeace(peaceName, theStream));
	});

	parseFile("ai_peaces.txt");
}


void HoI4::AIPeaces::updateAIPeaces(const std::set<std::string>& majorIdeologies)
{
	auto fascistPeace = std::find_if(thePeaces.begin(), thePeaces.end(), [](auto& thePeace){ return (thePeace.getName() == "fascist_peace"); });
	if (fascistPeace != thePeaces.end())
	{
		std::string newEnable = "= {\n";
		newEnable += "		OR = {\n";
		newEnable += "			has_government = fascism\n";
		newEnable += "			AND = {\n";
		for (auto ideology: majorIdeologies)
		{
			if ((ideology == "fascism") || (ideology == "neutrality"))
			{
				continue;
			}
			newEnable += "				NOT = { has_government = " + ideology + " }\n";
		}
		newEnable += "				OR = {\n";
		newEnable += "					any_country = {\n";
		newEnable += "						is_in_faction_with = ROOT\n";
		newEnable += "						is_faction_leader = yes\n";
		newEnable += "						has_government = fascism\n";
		newEnable += "					}\n";
		newEnable += "					is_in_faction = no\n";
		newEnable += "					is_faction_leader = yes\n";
		newEnable += "				}\n";
		newEnable += "			}\n";
		newEnable += "		}\n";
		newEnable += "	}";

		fascistPeace->replaceEnable(newEnable);
	}
}


void HoI4::AIPeaces::output(std::set<std::string> majorIdeologies)
{
	std::for_each(thePeaces.begin(), thePeaces.end(), [majorIdeologies](auto& thePeace){
		if (thePeace.getName() == "communist_peace")
		{
			std::ofstream outFile("output/" + theConfiguration.getOutputName() + "/common/ai_peace/1_communist.txt");
			if (majorIdeologies.count("communist") > 0)
			{
				outFile << thePeace;
			}
			outFile.close();
		}
		else if (thePeace.getName() == "fascist_peace")
		{
			std::ofstream outFile("output/" + theConfiguration.getOutputName() + "/common/ai_peace/1_fascist.txt");
			if (majorIdeologies.count("fascism") > 0)
			{
				outFile << thePeace;
			}
			outFile.close();
		}
		else if (thePeace.getName() == "democratic_peace")
		{
			std::ofstream outFile("output/" + theConfiguration.getOutputName() + "/common/ai_peace/1_democratic.txt");
			if (majorIdeologies.count("democratic") > 0)
			{
				outFile << thePeace;
			}
			outFile.close();
		}
	});
}