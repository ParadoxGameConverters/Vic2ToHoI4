#include "src/OutHoi4/OutSharedFocus.h"



std::ostream& HoI4::operator<<(std::ostream& output, const SharedFocus& focus)
{
	output << "shared_focus = {\n";
	output << "\tid = " << focus.id << "\n";
	output << "\ticon = " << focus.icon << "\n";
	if (!focus.text.empty())
	{
		output << "\ttext = " << focus.text << "\n";
	}
	for (const auto& prerequisite: focus.prerequisites)
	{
		output << "\tprerequisite " << prerequisite << "\n";
	}
	if (!focus.mutuallyExclusive.empty())
	{
		output << "\tmutually_exclusive " << focus.mutuallyExclusive << "\n";
	}
	if (!focus.bypass.empty())
	{
		output << "\tbypass " << focus.bypass << "\n";
	}
	output << "\tx = " << focus.xPos << "\n";
	output << "\ty = " << focus.yPos << "\n";
	if (!focus.relativePositionId.empty())
	{
		output << "\trelative_position_id = " << focus.relativePositionId << "\n";
	}
	output << "\tcost = " << focus.cost << "\n";
	if (focus.availableIfCapitulated)
	{
		output << "\tavailable_if_capitulated = yes\n";
	}
	if (!focus.available.empty())
	{
		output << "\tavailable " << focus.available << "\n";
	}
	if (!focus.cancelIfInvalid.empty())
	{
		output << "\tcancel_if_invalid = " << focus.cancelIfInvalid << "\n";
	}
	if (!focus.continueIfInvalid.empty())
	{
		output << "\tcontinue_if_invalid = " << focus.continueIfInvalid << "\n";
	}
	if (!focus.selectEffect.empty())
	{
		output << "\tselect_effect " << focus.selectEffect << "\n";
	}
	if (!focus.completeTooltip.empty())
	{
		output << "\tcomplete_tooltip " << focus.completeTooltip << "\n";
	}
	output << "\tcompletion_reward " << focus.completionReward << "\n";
	if (!focus.aiWillDo.empty())
	{
		output << "\tai_will_do " << focus.aiWillDo << "\n";
	}

	output << "}\n";
	output << "\n";

	return output;
}