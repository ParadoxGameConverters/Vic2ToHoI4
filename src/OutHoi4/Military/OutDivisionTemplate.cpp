#include "src/OutHoi4/Military/OutDivisionTemplate.h"



std::ostream& HoI4::operator<<(std::ostream& out, const DivisionTemplateType& rhs)
{
	out << "division_template = {\n";
	out << "\tname = \"" << rhs.name << "\"\n";
	out << "\n";
	out << "\tregiments = {\n";
	for (const auto& regiment: rhs.regiments)
	{
		out << regiment;
	}
	out << "\t}\n";
	out << "\tsupport = {\n";
	for (const auto& regiment: rhs.supportRegiments)
	{
		out << regiment;
	}
	out << "\t}\n";
	out << "}\n";

	return out;
}