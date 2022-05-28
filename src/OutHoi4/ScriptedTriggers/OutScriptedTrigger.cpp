#include "OutScriptedTrigger.h"



std::ostream& HoI4::operator<<(std::ostream& output, const ScriptedTrigger& scriptedTrigger)
{
	output << "\n";
	output << scriptedTrigger.name << " ";
	output << scriptedTrigger.body;
	output << "\n";

	return output;
}