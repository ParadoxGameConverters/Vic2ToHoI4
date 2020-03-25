#include "OutIdeologies.h"
#include "OSCompatibilityLayer.h"



void HoI4::outputIdeologies(const Ideologies& ideologies)
{
	if (!Utils::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/common/ideologies/"))
	{
		Log(LogLevel::Error) << "Could not create output/" + theConfiguration.getOutputName() + "/common/ideologies/";
	}
	std::ofstream ideologyFile("output/" + theConfiguration.getOutputName() + "/common/ideologies/00_ideologies.txt");
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