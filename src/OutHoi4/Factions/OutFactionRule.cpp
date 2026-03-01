#include "src/OutHoi4/Factions/OutFactionRule.h"



std::ostream& HoI4::operator<<(std::ostream& out, const FactionRule& theRule)
{
	out << theRule.id << " = {\n";
	out << "\ttype = " << theRule.type << "\n";
	if (theRule.visible)
	{
		out << "\tvisible " << *theRule.visible << "\n";
	}
	if (theRule.available)
	{
		out << "\tavailable " << *theRule.available << "\n";
	}
	if (theRule.canRemove)
	{
		out << "\tcan_remove " << *theRule.canRemove << "\n";
	}
	if (theRule.trigger)
	{
		out << "\ttrigger " << *theRule.trigger << "\n";
	}
	if (theRule.dismissMemberTrigger)
	{
		out << "\tdismiss_member_trigger " << *theRule.dismissMemberTrigger << "\n";
	}
	if (theRule.governmentInExileAllowedTrigger)
	{
		out << "\tgovernment_in_exile_allowed_trigger " << *theRule.governmentInExileAllowedTrigger << "\n";
	}
	if (theRule.peaceActionModifiers)
	{
		out << "\tpeace_action_modifiers " << *theRule.peaceActionModifiers << "\n";
	}
	if (theRule.modifier)
	{
		out << "\tmodifier " << *theRule.modifier << "\n";
	}
	if (theRule.effect)
	{
		out << "\teffect " << *theRule.effect << "\n";
	}
	if (theRule.aiWillDo)
	{
		out << "\tai_will_do " << *theRule.aiWillDo << "\n";
	}
	out << "}\n";

	return out;
}