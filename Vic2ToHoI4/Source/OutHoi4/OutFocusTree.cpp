#include "OutFocusTree.h"
#include "OutFocus.h"
#include <fstream>
#include <string>



void HoI4::outputFocusTree(const HoI4FocusTree& focusTree, const std::string& filename)
{
	std::ofstream out(filename);
	if (!out.is_open())
	{
		throw std::runtime_error("Could not create " + filename);
	}

	out << "focus_tree = {\n";
	if (!focusTree.getDestinationCountryTag().empty())
	{
		out << "\tid = " << focusTree.getDestinationCountryTag() + "_focus\n";
		out << "\t\n";
		out << "\tcountry = {\n";
		out << "\t\tfactor = 0\n";
		out << "\t\t\n";
		out << "\t\tmodifier = {\n";
		out << "\t\t\tadd = 10\n";
		out << "\t\t\ttag = " << focusTree.getDestinationCountryTag() << "\n";
		out << "\t\t}\n";
		out << "\t}\n";
		out << "\t\n";
		out << "\tdefault = no\n";
		out << "\t\n";
		out << "\tshared_focus = army_effort\n";
		out << "\tshared_focus = aviation_effort\n";
		out << "\tshared_focus = naval_effort\n";
		out << "\tshared_focus = industrial_effort\n";
		out << "\tshared_focus = political_effort\n";
		out << "\n";
	}

	for (const auto& focus: focusTree.getFocuses())
	{
		out << *focus;
		out << "\n";
	}

	out << "}";

	out.close();
}

// move this to its own file
void outputShared(std::ostream& output, const HoI4Focus& focus)
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
}


void HoI4::outputSharedFocuses(const HoI4FocusTree& focusTree, const std::string& filename)
{
	std::ofstream SharedFocuses(filename);
	if (!SharedFocuses.is_open())
	{
		throw std::runtime_error("Could not create " + filename);
	}

	for (const auto& focus: focusTree.getSharedFocuses())
	{
		outputShared(SharedFocuses, *focus);
	}

	SharedFocuses.close();
}