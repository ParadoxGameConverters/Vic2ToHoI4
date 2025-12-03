#include "src/OutHoi4/Factions/OutFactionGoal.h"



std::ostream& HoI4::operator<<(std::ostream& out, const FactionGoal& theGoal)
{
	out << theGoal.id << " = {\n";
	out << "\tname = " << theGoal.name << "\n";
	out << "\tdescription = " << theGoal.description << "\n";
	if (theGoal.isManifest)
	{
		out << "\tis_manifest = yes\n";
		out << "\tratio_progress " << theGoal.ratioProgress << "\n";
		out << "}\n";
		out << "\n";
		return out;
	}

	out << "\tgroup = " << theGoal.group << "\n";
	out << "\tcategory = " << theGoal.category << "\n";
	out << "\tvisible " << theGoal.visible << "\n";
	if (theGoal.lockedGoal)
	{
		out << "\tlocked_goal = yes\n";
	}
	out << "\tavailable " << theGoal.available << "\n";
	out << "\tcompleted " << theGoal.completed << "\n";
	out << "\tcomplete_effect " << theGoal.completeEffect << "\n";
	out << "\tai_will_do " << theGoal.aiWillDo << "\n";
	out << "}\n";
	out << "\n";

	return out;
}