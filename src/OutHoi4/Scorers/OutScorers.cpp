#include "src/OutHoi4/Scorers/OutScorers.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/OutHoi4/Scorers/OutScorer.h"
#include <fstream>
#include <ranges>



void HoI4::outputScorers(const Scorers& scorers, const Configuration& configuration)
{
	const std::filesystem::path folder =
		 std::filesystem::path("output") / configuration.getOutputName() / "common/scorers/country";
	if (!commonItems::DoesFolderExist(folder) && !std::filesystem::create_directories(folder))
	{
		throw std::runtime_error("Could not create " + folder.string());
	}

	const std::filesystem::path file = std::filesystem::path("output") / configuration.getOutputName() /
												  "common/scorers/country/generic_platonic_scorers.txt";
	std::ofstream output(file);
	if (!output.is_open())
	{
		throw std::runtime_error("Could not create " + file.string());
	}

	for (const auto& scorer: scorers.getCustomizedScorers() | std::views::values)
	{
		output << scorer;
		output << "\n";
	}

	output.close();
}