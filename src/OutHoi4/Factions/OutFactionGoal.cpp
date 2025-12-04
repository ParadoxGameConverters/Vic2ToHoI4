#include "src/OutHoi4/Factions/OutFactionGoal.h"



std::ostream& HoI4::operator<<(std::ostream& out, const FactionGoal& theGoal)
{
	out << theGoal.id << " = {\n";
	out << "\tname = " << theGoal.name << "\n";
	out << "\tdescription = " << theGoal.description << "\n";
	if (theGoal.group)
	{
		out << "\tgroup = " << *theGoal.group << "\n";
	}
	if (theGoal.category)
	{
		out << "\tcategory = " << *theGoal.category << "\n";
	}
	if (theGoal.allowed)
	{
		out << "\tallowed " << *theGoal.allowed << "\n";
	}
	if (theGoal.visible)
	{
		out << "\tvisible " << *theGoal.visible << "\n";
	}
	if (theGoal.lockedGoal)
	{
		out << "\tlocked_goal = yes\n";
	}
	if (theGoal.available)
	{
		out << "\tavailable " << *theGoal.available << "\n";
	}
	if (theGoal.selectEffect)
	{
		out << "\tselect_effect " << *theGoal.selectEffect << "\n";
	}
	if (theGoal.completed)
	{
		out << "\tcompleted " << *theGoal.completed << "\n";
	}
	if (theGoal.cancel)
	{
		out << "\tcancel " << *theGoal.cancel << "\n";
	}
	if (theGoal.autoComplete)
	{
		out << "\tauto_complete = yes\n";
	}
	if (theGoal.isManifest)
	{
		out << "\tis_manifest = yes\n";
	}
	if (theGoal.ratioProgress)
	{
		out << "\tratio_progress " << *theGoal.ratioProgress << "\n";
	}
	if (theGoal.completeEffect)
	{
		out << "\tcomplete_effect " << *theGoal.completeEffect << "\n";
	}
	if (theGoal.aiWillDo)
	{
		out << "\tai_will_do " << *theGoal.aiWillDo << "\n";
	}
	out << "}\n";

	return out;
}