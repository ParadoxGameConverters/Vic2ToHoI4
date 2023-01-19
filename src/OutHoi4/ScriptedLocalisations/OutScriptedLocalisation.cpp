#include "src/OutHoi4/ScriptedLocalisations/OutScriptedLocalisation.h"



std::ostream& HoI4::operator<<(std::ostream& out, const ScriptedLocalisation& localisation)
{
	out << "defined_text = {\n";
	out << "\tname = " << localisation.getName() << "\n";
	for (const auto& text: localisation.getTexts())
	{
		out << "\ttext " << text << "\n";
	}
	out << "}\n";

	return out;
}