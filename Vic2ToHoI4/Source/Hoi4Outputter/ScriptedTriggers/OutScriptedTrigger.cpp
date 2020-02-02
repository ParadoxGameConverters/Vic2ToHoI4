#include "OutScriptedTrigger.h"



std::ostream& HoI4::operator<<(std::ostream& output, const ScriptedTrigger& scriptedTrigger)
{
	output << "\n";
	output << scriptedTrigger.name << " = {\n";
	output << scriptedTrigger.body << "\n";
	output << "}\n";

	return output;
}