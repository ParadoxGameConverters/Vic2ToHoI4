#include "outDifficultySettings.h"
#include <fstream>

void HoI4::outputDifficultySettings(
	const std::vector<std::shared_ptr<HoI4::Country>>& greatPowers,
	const Configuration& theConfiguration
) {
	std::ofstream outStream;

	outStream.open("output/" + theConfiguration.getOutputName() + "/common/difficulty_settings/00_difficulty.txt");
	outStream << "difficulty_settings = {\n";
	for (const auto& GP: greatPowers)
	{
		outStream << "\tdifficulty_setting = {\n";
		outStream << "\t\tkey = \"custom_diff_strong_" + GP->getTag() + "\"\n";
		outStream << "\t\tmodifier = diff_strong_ai_generic\n";
		outStream << "\t\tcountries = { " + GP->getTag() + " }\n";
		outStream << "\t\tmultiplier = 2.0\n";
		outStream << "\t}\n";
	}
	outStream << "}\n";
	outStream.close();
}