#include "OutScriptedTriggers.h"
#include <fstream>



void HoI4::outputScriptedTriggers(const ScriptedTriggers& scriptedTriggers, const Configuration& theConfiguration)
{
	std::ofstream outIdeology(
		"output/" + theConfiguration.getOutputName() + "/common/scripted_triggers/ideology_scripted_triggers.txt",
		std::ostream::app
	);
	for (const auto& scriptedTrigger: scriptedTriggers.getIdeologyScriptedTriggers())
	{
		outIdeology << scriptedTrigger;
	}
	outIdeology.close();

	std::ofstream outElections(
		"output/" + theConfiguration.getOutputName() + "/common/scripted_triggers/Elections_scripted_triggers.txt",
		std::ostream::app
	);
	for (const auto& scriptedTrigger: scriptedTriggers.getElectionsScriptedTriggers())
	{
		outElections << scriptedTrigger;
	}
	outElections.close();

	std::ofstream outLawsWarSupport(
		"output/" + theConfiguration.getOutputName() + "/common/scripted_triggers/laws_war_support.txt",
		std::ostream::app
	);
	for (const auto& scriptedTrigger : scriptedTriggers.getLawsWarSupportTriggers())
	{
		outLawsWarSupport << scriptedTrigger;
	}
	outLawsWarSupport.close();
}