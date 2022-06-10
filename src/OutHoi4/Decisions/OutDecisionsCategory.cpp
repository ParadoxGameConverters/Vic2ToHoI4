#include "src/OutHoi4/Decisions/OutDecisionsCategory.h"



std::ostream& HoI4::operator<<(std::ostream& out, const DecisionsCategory& decisionsCategory)
{
	out << decisionsCategory.name << " = {\n";
	if (!decisionsCategory.icon.empty())
	{
		out << "\ticon = " << decisionsCategory.icon << "\n";
	}
	if (!decisionsCategory.picture.empty())
	{
		out << "\tpicture = " << decisionsCategory.picture << "\n";
	}
	if (decisionsCategory.priority)
	{
		out << "\tpriority = " << *decisionsCategory.priority << "\n";
	}
	if (!decisionsCategory.allowed.empty())
	{
		out << "\tallowed " << decisionsCategory.allowed << "\n";
	}
	if (!decisionsCategory.visible.empty())
	{
		out << "\tvisible " << decisionsCategory.visible << "\n";
	}
	if (!decisionsCategory.visibilityType.empty())
	{
		out << "\tvisibility_type " << decisionsCategory.visibilityType << "\n";
	}
	for (const auto& extraItem: decisionsCategory.extraItems)
	{
		out << "\t" << extraItem.first << " " << extraItem.second << "\n";
	}
	out << "}\n";
	out << "\n";

	return out;
}