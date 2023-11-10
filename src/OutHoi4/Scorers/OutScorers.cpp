#include "src/OutHoi4/Scorers/OutScorers.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/OutHoi4/Scorers/OutScorer.h"
#include <fstream>
#include <ranges>



void HoI4::outputScorers(const Scorers& scorers, const Configuration& configuration)
{
	if (!commonItems::TryCreateFolder("output/" + configuration.getOutputName() + "/common/scorers/country/"))
	{
		throw std::runtime_error("Could not create output/" + configuration.getOutputName() + "/common/scorers/country/");
	}

	std::ofstream output("output/" + configuration.getOutputName() + "/common/scorers/country/generic_platonic_scorers.txt");
	if (!output.is_open())
	{
		throw std::runtime_error(
			 "Could not create output/" + configuration.getOutputName() + "/common/scorers/country/generic_platonic_scorers.txt");
	}

	for (const auto& scorer: scorers.getCustomizedScorers() | std::views::values)
	{
		output << scorer;
		output << "\n";
	}

	output.close();
}