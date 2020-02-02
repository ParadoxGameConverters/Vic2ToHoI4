#include "OutScriptedTriggers.h"
#include <fstream>



void HoI4::outputScriptedTriggers(const ScriptedTriggers& scriptedTriggers, const Configuration& theConfiguration)
{
	std::ofstream outStream(
		"output/" + theConfiguration.getOutputName() + "/common/scripted_triggers/ideology_scripted_triggers.txt",
		std::ostream::app
	);

	for (const auto& scriptedTrigger: scriptedTriggers.getIdeologyScriptedTriggers())
	{
		outStream << scriptedTrigger;
	}
	
	outStream.close();
}