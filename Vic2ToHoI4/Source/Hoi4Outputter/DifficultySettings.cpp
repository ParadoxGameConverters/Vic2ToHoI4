#include "DifficultySettings.h"
#include <fstream>

void HoI4::outputDifficultySettings(std::string difficultySettings, const Configuration& theConfiguration)
{
	std::ofstream outStream;

	outStream.open("output/" + theConfiguration.getOutputName() + "/common/difficulty_settings/00_difficulty.txt");
	outStream << "difficulty_settings = {\n";
	outStream << difficultySettings;
	outStream << "}\n";
	outStream.close();
}