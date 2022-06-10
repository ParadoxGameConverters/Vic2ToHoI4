#include "src/OutHoi4/ScriptedTriggers/OutScriptedTriggers.h"
#include <fstream>



void HoI4::outputScriptedTriggers(const ScriptedTriggers& scriptedTriggers, const std::string& outputName)
{
	std::ofstream outIdeology("output/" + outputName + "/common/scripted_triggers/ideology_scripted_triggers.txt",
		 std::ostream::app);
	for (const auto& scriptedTrigger: scriptedTriggers.getIdeologyScriptedTriggers())
	{
		outIdeology << scriptedTrigger;
	}
	outIdeology.close();

	std::ofstream outElections("output/" + outputName + "/common/scripted_triggers/Elections_scripted_triggers.txt",
		 std::ostream::app);
	for (const auto& scriptedTrigger: scriptedTriggers.getElectionsScriptedTriggers())
	{
		outElections << scriptedTrigger;
	}
	outElections.close();

	std::ofstream outLawsWarSupport("output/" + outputName + "/common/scripted_triggers/laws_war_support.txt",
		 std::ostream::app);
	for (const auto& scriptedTrigger: scriptedTriggers.getLawsWarSupportTriggers())
	{
		outLawsWarSupport << scriptedTrigger;
	}
	outLawsWarSupport.close();

	std::ofstream outNationalFocus("output/" + outputName + "/common/scripted_triggers/nf_triggers.txt",
		 std::ostream::app);
	for (const auto& scriptedTrigger: scriptedTriggers.getNationalFocusTriggers())
	{
		outNationalFocus << scriptedTrigger;
	}
	outNationalFocus.close();
}