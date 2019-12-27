#include "ScriptedLocalisationsOutputter.h"
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
		scriptedLocalisationsFile << "defined_text = {\n";
		scriptedLocalisationsFile << "\tname = " << localisation.getName() << "\n";
		for (auto text: localisation.getTexts())
		{
			scriptedLocalisationsFile << "\ttext = {\n";
			scriptedLocalisationsFile << text;
			scriptedLocalisationsFile << "\t}\n";
		}
		scriptedLocalisationsFile << "}\n";
	}

	scriptedLocalisationsFile.close();
}