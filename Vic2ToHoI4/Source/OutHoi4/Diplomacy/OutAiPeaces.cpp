#include "OutAiPeaces.h"
#include <fstream>



void HoI4::outAiPeaces(const AiPeaces& aiPeaces,
	 const std::set<std::string>& majorIdeologies,
	 const std::string& outputName)
{
	auto thePeaces = aiPeaces.getThePeaces();
	for (const auto& thePeace: thePeaces)
	{
		if (thePeace.getName() == "communist_peace")
		{
			std::ofstream outFile("output/" + outputName + "/common/ai_peace/1_communist.txt");
			if (majorIdeologies.count("communist") > 0)
			{
				outFile << thePeace;
			}
			outFile.close();
		}
		else if (thePeace.getName() == "fascist_peace")
		{
			std::ofstream outFile("output/" + outputName + "/common/ai_peace/1_fascist.txt");
			if (majorIdeologies.count("fascism") > 0)
			{
				outFile << thePeace;
			}
			outFile.close();
		}
		else if (thePeace.getName() == "democratic_peace")
		{
			std::ofstream outFile("output/" + outputName + "/common/ai_peace/1_democratic.txt");
			if (majorIdeologies.count("democratic") > 0)
			{
				outFile << thePeace;
			}
			outFile.close();
		}
	}
}