#include "OutFocus.h"



std::ostream& operator<<(std::ostream& output, const HoI4Focus& focus)
{
	output << "\tfocus = {\n";
	output << "\t\tid = " << focus.id << "\n";
	output << "\t\ticon = " << focus.icon << "\n";
	if (!focus.text.empty())
	{
		output << "\t\ttext = " << focus.text << "\n";
	}
	for (const auto& prerequisite: focus.prerequisites)
	{
		output << "\t\tprerequisite " << prerequisite << "\n";
	}
	if (!focus.mutuallyExclusive.empty())
	{
		output << "\t\tmutually_exclusive " << focus.mutuallyExclusive << "\n";
	}
	if (!focus.bypass.empty())
	{
		output << "\t\tbypass " << focus.bypass << "\n";
	}
	output << "\t\tx = " << focus.xPos << "\n";
	output << "\t\ty = " << focus.yPos << "\n";
	if (!focus.relativePositionId.empty())
	{
		output << "\t\trelative_position_id = " << focus.relativePositionId << "\n";
	}
	output << "\t\tcost = " << focus.cost << "\n";
	if (focus.availableIfCapitulated)
	{
		output << "\t\tavailable_if_capitulated = yes\n";
	}
	if (!focus.available.empty())
	{
		output << "\t\tavailable " << focus.available << "\n";
	}
	if (!focus.cancelIfInvalid.empty())
	{
		output << "\t\tcancel_if_invalid = " << focus.cancelIfInvalid << "\n";
	}
	if (!focus.continueIfInvalid.empty())
	{
		output << "\t\tcontinue_if_invalid = " << focus.continueIfInvalid << "\n";
	}
	if (!focus.selectEffect.empty())
	{
		output << "\t\tselect_effect " << focus.selectEffect << "\n";
	}
	if (!focus.completeTooltip.empty())
	{
		output << "\t\tcomplete_tooltip " << focus.completeTooltip << "\n";
	}
	output << "\t\tcompletion_reward " << focus.completionReward << "\n";
	if (!focus.aiWillDo.empty())
	{
		output << "\t\tai_will_do " << focus.aiWillDo << "\n";
	}
	if (!focus.allowBranch.empty())
	{
		output << "\t\tallow_branch " << focus.allowBranch << "\n";
	}

	output << "\t}\n";

	return output;
}