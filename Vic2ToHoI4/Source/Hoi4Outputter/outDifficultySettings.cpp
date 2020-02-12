#include "../Configuration.h"
#include "../HOI4World/HoI4Country.h"
#include <fstream>

void outputDifficultySettings(
	const std::vector<std::shared_ptr<HoI4::Country>>& greatPowers,
	const Configuration& theConfiguration
) {
	std::string diffSet = "";
	for (const auto& GP: greatPowers)
	{
		diffSet += "\tdifficulty_setting = {\n";
		diffSet += "\t\tkey = \"custom_diff_strong_" + GP->getTag() + "\"\n";
		diffSet += "\t\tmodifier = diff_strong_ai_generic\n";
		diffSet += "\t\tcountries = { " + GP->getTag() + " }\n";
		diffSet += "\t\tmultiplier = 2.0\n";
		diffSet += "\t}\n";
	}

	std::ofstream outStream;

	outStream.open("output/" + theConfiguration.getOutputName() + "/common/difficulty_settings/00_difficulty.txt");
	outStream << "difficulty_settings = {\n";
	outStream << diffSet;
	outStream << "}\n";
	outStream.close();
}