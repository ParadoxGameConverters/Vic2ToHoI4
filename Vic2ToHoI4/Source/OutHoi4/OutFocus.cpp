#include "OutFocus.h"



std::ostream& operator<<(std::ostream& output, const HoI4Focus& focus)
{
	output << "	focus = {\n";
	output << "		id = " << focus.id << "\n";
	output << "		icon = " << focus.icon << "\n";
	if (!focus.text.empty())
	{
		output << "		text = " << focus.text << "\n";
	}
	for (const auto& prerequisite: focus.prerequisites)
	{
		output << "		prerequisite " << prerequisite << "\n";
	}
	if (!focus.mutuallyExclusive.empty())
	{
		output << "		mutually_exclusive " << focus.mutuallyExclusive << "\n";
	}
	if (!focus.bypass.empty())
	{
		output << "		bypass " << focus.bypass << "\n";
	}
	output << "		x = " << focus.xPos << "\n";
	output << "		y = " << focus.yPos << "\n";
	if (!focus.relativePositionId.empty())
	{
		output << "		relative_position_id = " << focus.relativePositionId << "\n";
	}
	output << "		cost = " << focus.cost << "\n";
	if (focus.availableIfCapitulated)
	{
		output << "		available_if_capitulated = yes\n";
	}
	if (!focus.available.empty())
	{
		output << "		available " << focus.available << "\n";
	}
	if (!focus.cancelIfInvalid.empty())
	{
		output << "		cancel_if_invalid = " << focus.cancelIfInvalid << "\n";
	}
	if (!focus.continueIfInvalid.empty())
	{
		output << "		continue_if_invalid = " << focus.continueIfInvalid << "\n";
	}
	if (!focus.completeTooltip.empty())
	{
		output << "		complete_tooltip " << focus.completeTooltip << "\n";
	}
	output << "		completion_reward " << focus.completionReward << "\n";
	if (!focus.aiWillDo.empty())
	{
		output << "		ai_will_do " << focus.aiWillDo << "\n";
	}

	output << "	}\n";

	return output;
}