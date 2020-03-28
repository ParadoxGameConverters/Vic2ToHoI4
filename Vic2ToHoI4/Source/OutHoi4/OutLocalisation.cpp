#include "OutLocalisation.h"
#include "../Configuration.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include <fstream>



void outputLocalisations(const std::string& filenameStart, const languageToLocalisationsMap& localisations)
{
	for (const auto& languageToLocalisations: localisations)
	{
		if (languageToLocalisations.first == "")
		{
			continue;
		}
		std::ofstream localisationFile(filenameStart + languageToLocalisations.first + ".yml", std::ios_base::app);
		if (!localisationFile.is_open())
		{
			LOG(LogLevel::Error) << "Could not update localisation text file";
			exit(-1);
		}
		localisationFile << "\xEF\xBB\xBF"; // output a BOM to make HoI4 happy
		localisationFile << "l_" << languageToLocalisations.first << ":\n";

		for (const auto& mapping: languageToLocalisations.second)
		{
			localisationFile << " " << mapping.first << ":10 \"" << mapping.second << "\"" << std::endl;
		}
	}
}


void outputStateLocalisations(const std::string& localisationPath,
	 const std::map<language, std::map<stateNumber, std::string>>& stateLocalisations)
{
	for (const auto& languageToLocalisations: stateLocalisations)
	{
		if (languageToLocalisations.first == "")
		{
			continue;
		}
		std::ofstream localisationFile(localisationPath + "/state_names_l_" + languageToLocalisations.first + ".yml",
			 std::ios_base::app);
		if (!localisationFile.is_open())
		{
			LOG(LogLevel::Error) << "Could not update state localisation text file";
			exit(-1);
		}
		localisationFile << "\xEF\xBB\xBF"; // output a BOM to make HoI4 happy
		localisationFile << "l_" << languageToLocalisations.first << ":\n";

		for (const auto& mapping: languageToLocalisations.second)
		{
			localisationFile << " STATE_" << mapping.first << ":10 \"" << mapping.second << "\"" << std::endl;
		}
	}
}


void HoI4::outputLocalisation(const HoI4Localisation& localisation, const std::string& outputName)
{
	LOG(LogLevel::Debug) << "Writing localisations";
	const auto localisationPath = "output/" + outputName + "/localisation";
	if (!Utils::TryCreateFolder(localisationPath))
	{
		LOG(LogLevel::Error) << "Could not create localisation folder";
		exit(-1);
	}

	outputLocalisations(localisationPath + "/countries_mod_l_", localisation.getCountryLocalisations());
	outputLocalisations(localisationPath + "/focus_mod_l_", localisation.getNewFocuses());
	outputStateLocalisations(localisationPath, localisation.getStateLocalisations());
	outputLocalisations(localisationPath + "/victory_points_l_", localisation.getVPLocalisations());
	outputLocalisations(localisationPath + "/converted_ideas_l_", localisation.getIdeaLocalisations());
	outputLocalisations(localisationPath + "/converted_events_l_", localisation.getNewEventLocalisations());
	outputLocalisations(localisationPath + "/parties3_l_", localisation.getPoliticalPartyLocalisations());
	outputLocalisations(localisationPath + "/decisions3_l_", localisation.getDecisionLocalisations());
	outputLocalisations(localisationPath + "/custom_localization_converter_l_", localisation.getCustomLocalisations());
}