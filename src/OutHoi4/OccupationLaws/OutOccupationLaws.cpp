#include "src/OutHoi4/OccupationLaws/OutOccupationLaws.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/OutHoi4/OccupationLaws/OutOccupationLaw.h"
#include <fstream>



void HoI4::outputOccupationLaws(const OccupationLaws& occupationLaws, const Configuration& configuration)
{
	if (!commonItems::TryCreateFolder("output/" + configuration.getOutputName() + "/common/occupation_laws/"))
	{
		throw std::runtime_error("Could not create output/" + configuration.getOutputName() + "/common/occupation_laws/");
	}

	std::ofstream output("output/" + configuration.getOutputName() + "/common/occupation_laws/occupation_laws.txt");
	if (!output.is_open())
	{
		throw std::runtime_error(
			 "Could not create output/" + configuration.getOutputName() + "/common/occupation_laws/occupation_laws.txt");
	}

	for (const auto& occupationLaw: occupationLaws.getOccupationLaws())
	{
		output << occupationLaw;
		output << "\n";
	}

	output.close();
}