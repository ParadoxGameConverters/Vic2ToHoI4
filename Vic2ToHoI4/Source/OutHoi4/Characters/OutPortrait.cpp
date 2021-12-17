#include "OutPortrait.h"



std::ostream& HoI4::operator<<(std::ostream& out, const Portrait& portrait)
{
	out << "\t\t\t" << portrait.getType() << "={\n";
	out << "\t\t\t\t" << portrait.getSize() << "=\"" << portrait.getDefinition() << "\"\n";
	out << "\t\t\t}\n";

	return out;
}