#include "src/OutHoi4/OccupationLaws/OutOccupationLaws.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/OutHoi4/OccupationLaws/OutOccupationLaw.h"
#include <fstream>



void HoI4::outputOccupationLaws(const OccupationLaws& occupationLaws, const Configuration& configuration)
{
	const std::filesystem::path folder =
		 std::filesystem::path("output") / configuration.getOutputName() / "common/occupation_laws";
	if (!commonItems::DoesFolderExist(folder) && !std::filesystem::create_directories(folder))
	{
		throw std::runtime_error("Could not create " + folder.string());
	}

	const std::filesystem::path file =
		 std::filesystem::path("output") / configuration.getOutputName() / "common/occupation_laws/occupation_laws.txt";
	std::ofstream output(file);
	if (!output.is_open())
	{
		throw std::runtime_error("Could not create " + file.string());
	}

	for (const auto& occupationLaw: occupationLaws.getOccupationLaws())
	{
		output << occupationLaw;
		output << "\n";
	}

	output.close();
}