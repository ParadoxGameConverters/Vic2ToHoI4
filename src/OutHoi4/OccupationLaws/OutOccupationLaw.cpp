#include "src/OutHoi4/OccupationLaws/OutOccupationLaw.h"



std::ostream& HoI4::operator<<(std::ostream& output, const OccupationLaw& occupationLaw)
{
	output << occupationLaw.getName() << " = {\n";
	output << "\ticon = " << occupationLaw.getIcon() << "\n";
	if (occupationLaw.getDefaultLaw())
	{
		output << "\tdefault_law = yes\n";
	}
	output << "\tsound_effect = \"" << occupationLaw.getSoundEffect() << "\"\n";
	if (occupationLaw.getVisible())
	{
		output << "\n";
		output << "\tvisible " << *occupationLaw.getVisible() << "\n";
	}
	output << "\n";
	output << "\tstate_modifier " << occupationLaw.getStateModifier() << "\n";
	if (occupationLaw.getSuppressedStateModifier())
	{
		output << "\n";
		output << "\tsuppressed_state_modifier " << *occupationLaw.getSuppressedStateModifier() << "\n";
	}
	if (occupationLaw.getStartingLaw())
	{
		output << "\tstarting_law = yes\n";
	}
	if (occupationLaw.getAiWillDo())
	{
		output << "\n";
		output << "\tai_will_do " << *occupationLaw.getAiWillDo() << "\n";
	}
	output << "}\n";

	return output;
}