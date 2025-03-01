#include "src/OutHoi4/Ideologies/OutIdeologies.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include <fstream>



void HoI4::outputIdeologies(const Ideologies& ideologies, const std::filesystem::path& outputName)
{
	const std::filesystem::path folder = "output" / outputName / "common/ideologies";
	if (!commonItems::DoesFolderExist(folder) && !std::filesystem::create_directories(folder))
	{
		Log(LogLevel::Error) << "Could not create " + folder.string();
	}

	std::ofstream ideologyFile(folder / "00_ideologies.txt");
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