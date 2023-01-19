#include "src/OutHoi4/Ideologies/OutIdeologies.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include <fstream>



void HoI4::outputIdeologies(const Ideologies& ideologies, const std::string& outputName)
{
	if (!commonItems::TryCreateFolder("output/" + outputName + "/common/ideologies/"))
	{
		Log(LogLevel::Error) << "Could not create output/" + outputName + "/common/ideologies/";
	}
	std::ofstream ideologyFile("output/" + outputName + "/common/ideologies/00_ideologies.txt");
	ideologyFile << "ideologies = {\n";
	ideologyFile << "\t\n";
	for (const auto& ideologyName: ideologies.getMajorIdeologies())
	{
		auto ideology = ideologies.getIdeology(ideologyName);
		if (ideology)
		{
			ideologyFile << *ideology;
		}
	}
	ideologyFile << "}";
	ideologyFile.close();
}