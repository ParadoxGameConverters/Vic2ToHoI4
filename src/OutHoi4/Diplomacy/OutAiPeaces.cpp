#include "src/OutHoi4/Diplomacy/OutAiPeaces.h"
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
			if (majorIdeologies.contains("communism"))
			{
				outFile << thePeace;
			}
			outFile.close();
		}
		if (thePeace.getName() == "radical_peace")
		{
			std::ofstream outFile("output/" + outputName + "/common/ai_peace/1_radical.txt");
			if (majorIdeologies.contains("radical"))
			{
				outFile << thePeace;
			}
			outFile.close();
		}
		else if (thePeace.getName() == "fascist_peace")
		{
			std::ofstream outFile("output/" + outputName + "/common/ai_peace/1_fascist.txt");
			if (majorIdeologies.contains("fascism"))
			{
				outFile << thePeace;
			}
			outFile.close();
		}
		else if (thePeace.getName() == "absolutist_peace")
		{
			std::ofstream outFile("output/" + outputName + "/common/ai_peace/1_absolutist.txt");
			if (majorIdeologies.contains("absolutist"))
			{
				outFile << thePeace;
			}
			outFile.close();
		}
		else if (thePeace.getName() == "democratic_peace")
		{
			std::ofstream outFile("output/" + outputName + "/common/ai_peace/1_democratic.txt");
			if (majorIdeologies.contains("democratic"))
			{
				outFile << thePeace;
			}
			outFile.close();
		}
	}
}