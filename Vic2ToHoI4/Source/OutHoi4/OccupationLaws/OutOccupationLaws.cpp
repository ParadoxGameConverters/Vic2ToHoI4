#include "OutOccupationLaws.h"
#include "OutOccupationLaw.h"
#include <fstream>



void HoI4::outputOccupationLaws(const OccupationLaws& occupationLaws, const Configuration& configuration)
{
	std::ofstream output("output/" + configuration.getOutputName() + "/common/occupation_laws/occupation_laws.txt");
	if (!output.is_open())
	{
		throw std::runtime_error(
			 "Could not open output/" + configuration.getOutputName() + "/common/occupation_laws/occupation_laws.txt");
	}

	for (const auto& occupationLaw: occupationLaws.getOccupationLaws())
	{
		output << occupationLaw;
	}

	output.close();
}