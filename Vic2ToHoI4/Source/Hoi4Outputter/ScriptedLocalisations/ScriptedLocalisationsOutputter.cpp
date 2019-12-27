#include "ScriptedLocalisationsOutputter.h"
#include "ScriptedLocalisationOutputter.h"
#include <fstream>



void HoI4::outputScriptedLocalisations(
	const Configuration& theConfiguration,
	const ScriptedLocalisations& scriptedLocalisations
)
{
	std::ofstream scriptedLocalisationsFile(
		"output/" + theConfiguration.getOutputName() + "/common/scripted_localisation/00_scripted_localisation.txt",
		std::ofstream::app
	);

	for (auto localisation: scriptedLocalisations.getLocalisations())
	{
		scriptedLocalisationsFile << localisation;
	}

	scriptedLocalisationsFile.close();
}