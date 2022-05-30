#include "OutScriptedEffect.h"



std::ostream& HoI4::operator<<(std::ostream& out, const ScriptedEffect& scriptedEffect)
{
	out << scriptedEffect.getName() << " = {\n";
	for (const auto& [itemName, itemBody]: scriptedEffect.getItems())
	{
		out << '\t' << itemName << ' ' << itemBody << '\n';
	}
	out << "}\n";

	return out;
}