#include "src/OutHoi4/OutFocusTree.h"
#include "src/OutHoi4/OutFocus.h"
#include "src/OutHoi4/OutSharedFocus.h"
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
		if (!focusTree.isEmpty())
		{
			out << "\tshared_focus = army_effort\n";
			out << "\tshared_focus = aviation_effort\n";
			out << "\tshared_focus = naval_effort\n";
			out << "\tshared_focus = industrial_effort\n";
			out << "\tshared_focus = political_effort\n";
			out << "\n";
		}
	}

	for (const auto& focus: focusTree.getFocuses())
	{
		out << *focus;
		out << "\n";
	}

	out << "}";

	out.close();
}


void HoI4::outputSharedFocuses(const HoI4FocusTree& focusTree, const std::filesystem::path& filename)
{
	std::ofstream SharedFocuses(filename);
	if (!SharedFocuses.is_open())
	{
		throw std::runtime_error("Could not create " + filename.string());
	}

	for (const auto& focus: focusTree.getSharedFocuses())
	{
		SharedFocuses << *focus;
	}

	SharedFocuses.close();
}