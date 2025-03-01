#include "src/OutHoi4/ScriptedLocalisations/OutScriptedLocalisations.h"
#include "src/OutHoi4/ScriptedLocalisations/OutScriptedLocalisation.h"
#include <fstream>



void HoI4::outputScriptedLocalisations(const std::filesystem::path& outputName,
	 const ScriptedLocalisations& scriptedLocalisations)
{
	std::ofstream scriptedLocalisationsFile(
       "output" / outputName / "common/scripted_localisation/00_scripted_localisation.txt",
		 std::ofstream::app);
	for (const auto& localisation: scriptedLocalisations.getLocalisations())
	{
		scriptedLocalisationsFile << localisation;
	}
	scriptedLocalisationsFile.close();

	std::ofstream ideologyLocalisationsFile("output" / outputName / "common/scripted_localisation/ideologies.txt");
	for (const auto& localisation: scriptedLocalisations.getIdeologyLocalisations())
	{
		ideologyLocalisationsFile << localisation;
	}
	ideologyLocalisationsFile.close();

	for (const auto& localisationsInLanguage: scriptedLocalisations.getAdjectiveLocalisations())
	{
		auto filename = "output" / outputName / "common/scripted_localisation/000_scripted_localisation_";
		filename += localisationsInLanguage.first + "_loc.txt";
		std::ofstream adjectiveLocalisationsFile(filename, std::ofstream::app);

		for (const auto& localisation: localisationsInLanguage.second)
		{
			adjectiveLocalisationsFile << localisation;
		}

		adjectiveLocalisationsFile.close();
	}
}