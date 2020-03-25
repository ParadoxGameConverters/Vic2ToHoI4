#include "OutFocusTree.h"
#include "OutFocus.h"
#include "Log.h"
#include <fstream>
#include <string>



void HoI4::outputFocusTree(const HoI4FocusTree& focusTree, const std::string& filename)
{
	std::ofstream out(filename);
	if (!out.is_open())
	{
		LOG(LogLevel::Error) << "Could not create " << filename;
		exit(-1);
	}

	out << "focus_tree = {\n";
	if (!focusTree.getDestinationCountryTag().empty())
	{
		out << "	id = " << focusTree.getDestinationCountryTag() + "_focus\n";
		out << "	\n";
		out << "	country = {\n";
		out << "		factor = 0\n";
		out << "		\n";
		out << "		modifier = {\n";
		out << "			add = 10\n";
		out << "			tag = " << focusTree.getDestinationCountryTag() << "\n";
		out << "		}\n";
		out << "	}\n";
		out << "	\n";
		out << "	default = no\n";
		out << "	\n";
		out << "	shared_focus = army_effort\n";
		out << "	shared_focus = aviation_effort\n";
		out << "	shared_focus = naval_effort\n";
		out << "	shared_focus = industrial_effort\n";
		out << "	shared_focus = political_effort\n";
		out << "\n";
	}

	for (const auto& focus : focusTree.getFocuses())
	{
		out << *focus;
		out << "\n";
	}

	out << "}";

	out.close();
}


void outputShared(std::ostream& output, const HoI4Focus& focus)
{
	output << "shared_focus = {\n";
	output << "	id = " << focus.id << "\n";
	output << "	icon = " << focus.icon << "\n";
	if (!focus.text.empty())
	{
		output << "	text = " << focus.text << "\n";
	}
	for (auto prerequisite : focus.prerequisites)
	{
		output << "	prerequisite " << prerequisite << "\n";
	}
	if (!focus.mutuallyExclusive.empty())
	{
		output << "	mutually_exclusive " << focus.mutuallyExclusive << "\n";
	}
	if (!focus.bypass.empty())
	{
		output << "	bypass " << focus.bypass << "\n";
	}
	output << "	x = " << focus.xPos << "\n";
	output << "	y = " << focus.yPos << "\n";
	if (!focus.relativePositionId.empty())
	{
		output << "	relative_position_id = " << focus.relativePositionId << "\n";
	}
	output << "	cost = " << focus.cost << "\n";
	if (focus.availableIfCapitulated)
	{
		output << "	available_if_capitulated = yes\n";
	}
	if (!focus.available.empty())
	{
		output << "	available " << focus.available << "\n";
	}
	if (!focus.cancelIfInvalid.empty())
	{
		output << "	cancel_if_invalid = " << focus.cancelIfInvalid << "\n";
	}
	if (!focus.continueIfInvalid.empty())
	{
		output << "	continue_if_invalid = " << focus.continueIfInvalid << "\n";
	}
	if (!focus.completeTooltip.empty())
	{
		output << "	complete_tooltip " << focus.completeTooltip << "\n";
	}
	output << "	completion_reward " << focus.completionReward << "\n";
	if (!focus.aiWillDo.empty())
	{
		output << "	ai_will_do " << focus.aiWillDo << "\n";
	}

	output << "}\n";
	output << "\n";

	//return output;
}


void HoI4::outputSharedFocuses(const HoI4FocusTree& focusTree, const std::string& filename)
{
	std::ofstream SharedFoci(filename);
	if (!SharedFoci.is_open())
	{
		LOG(LogLevel::Error) << "Could not create " << filename;
		exit(-1);
	}

	for (auto focus : focusTree.getSharedFocuses())
	{
		outputShared(SharedFoci, *focus);
	}

	SharedFoci.close();
}