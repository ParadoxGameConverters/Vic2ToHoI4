/*Copyright (c) 2019 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#include "DecisionsCategory.h"
#include "../Events.h"



HoI4::decisionsCategory::decisionsCategory(const std::string& categoryName, std::istream& theStream):
	name(categoryName)
{
	registerKeyword(std::regex("[A-Za-z0-9\\_]+"), [this](const std::string& decisionName, std::istream& theStream)	{
		decision theDecision(decisionName, theStream);
		theDecisions.push_back(theDecision);
	});

	parseStream(theStream);
}


void HoI4::decisionsCategory::updatePoliticalDecisions(
	const std::set<std::string>& majorIdeologies,
	const Events& theEvents
) {
	for (auto& theDecision : theDecisions)
	{
		if (theDecision.getName().substr(0, 28) == "open_up_political_discourse_")
		{
			updateOpenUpPoliticalDiscourse(theDecision, majorIdeologies);
		}
		if (theDecision.getName().substr(0, 21) == "discredit_government_")
		{
			updateDiscreditGovernment(theDecision, majorIdeologies);
		}
		if (theDecision.getName().substr(0, 27) == "institute_press_censorship_")
		{
			updateInstitutePressCensorship(theDecision, majorIdeologies);
		}
		if (theDecision.getName().substr(0, 11) == "ignite_the_")
		{
			updateIgniteTheIdeologyCivilWar(theDecision, majorIdeologies);
		}
		if (theDecision.getName().substr(0, 9) == "hold_the_")
		{
			updateHoldTheIdeologyNationalReferendum(theDecision, theEvents);
		}
	}
}


void HoI4::decisionsCategory::updateOpenUpPoliticalDiscourse(
	decision& decisionToUpdate,
	const std::set<std::string>& majorIdeologies
) {
	std::string available = "= {\n";
	for (auto ideology : majorIdeologies)
	{
		available += "\t\t\t" + ideology + " < 0.9\n";
	}
	available += "\t\t}";
	decisionToUpdate.setAvailable(available);
}


void HoI4::decisionsCategory::updateDiscreditGovernment(
	decision& decisionToUpdate,
	const std::set<std::string>& majorIdeologies
) {
	std::string decisionIdeology = decisionToUpdate.getName().substr(21, decisionToUpdate.getName().length());
	std::string available = "= {\n";
	for (auto ideology : majorIdeologies)
	{
		available += "\t\t\t" + ideology + " < 0.8\n";
	}
	available += "\t\t\thas_idea_with_trait = " + decisionIdeology + "_minister\n";
	available += "\t\t}";
	decisionToUpdate.setAvailable(available);
	std::string completeEffect = "= {\n";
	completeEffect += "\t\t\tadd_stability = -0.010\n";
	for (auto ideology : majorIdeologies)
	{
		if (ideology == decisionIdeology)
		{
			continue;
		}
		completeEffect += "\t\t\tif = {\n";
		completeEffect += "\t\t\t\tlimit = {\n";
		completeEffect += "\t\t\t\t\thas_government = " + ideology + "\n";
		completeEffect += "\t\t\t\t}\n";
		completeEffect += "\t\t\t\tadd_popularity = {\n";
		completeEffect += "\t\t\t\t\tideology = " + ideology + "\n";
		completeEffect += "\t\t\t\t\tpopularity = -0.1\n";
		completeEffect += "\t\t\t\t}\n";
		completeEffect += "\t\t\t}\n";
	}
	completeEffect += "\t\t}";
	decisionToUpdate.setCompleteEffect(completeEffect);
}


void HoI4::decisionsCategory::updateInstitutePressCensorship(
	decision& decisionToUpdate,
	const std::set<std::string>& majorIdeologies
) {
	std::string decisionIdeology = decisionToUpdate.getName().substr(27, decisionToUpdate.getName().length());
	decisionIdeology = decisionIdeology.substr(0, decisionIdeology.find_last_of('_'));
	std::string modifier = "= {\n";
	for (auto ideology : majorIdeologies)
	{
		if (ideology == decisionIdeology)
		{
			modifier += "\t\t\t" + ideology + "_drift = 0.03\n";
		}
		else
		{
			modifier += "\t\t\t" + ideology + "_drift = -0.01\n";
		}
	}
	modifier += "\t\t}";
	decisionToUpdate.setModifier(modifier);
}


void HoI4::decisionsCategory::updateIgniteTheIdeologyCivilWar(
	decision& decisionToUpdate,
	const std::set<std::string>& majorIdeologies
) {
	std::string decisionIdeology = decisionToUpdate.getName().substr(11, decisionToUpdate.getName().length());
	decisionIdeology = decisionIdeology.substr(0, decisionIdeology.find_first_of('_'));
	std::string completeEffect = "= {\n";
	for (auto ideology : majorIdeologies)
	{
		if (ideology == decisionIdeology)
		{
			continue;
		}
		completeEffect += "\t\t\tif = {\n";
		completeEffect += "\t\t\t\tlimit = {\n";
		completeEffect += "\t\t\t\t\thas_government = " + ideology + "\n";
		completeEffect += "\t\t\t\t}\n";
		completeEffect += "\t\t\t\tset_variable = {\n";
		completeEffect += "\t\t\t\t\tvar = civil_war_size_var\n";
		completeEffect += "\t\t\t\t\tvalue = party_popularity@" + ideology + "\n";
		completeEffect += "\t\t\t\t}\n";
		completeEffect += "\t\t\t}\n";
	}
	completeEffect += "\t\t\tsubtract_from_variable = {\n";
	completeEffect += "\t\t\t\tvar = civil_war_size_var\n";
	completeEffect += "\t\t\t\tvalue = army_support_var\n";
	completeEffect += "\t\t\t}\n";
	completeEffect += "\t\t\tif = {\n";
	completeEffect += "\t\t\t\tlimit = {\n";
	completeEffect += "\t\t\t\t\tcheck_variable = {\n";
	completeEffect += "\t\t\t\t\t\tvar = civil_war_size_var\n";
	completeEffect += "\t\t\t\t\t\tvalue = 0.3\n";
	completeEffect += "\t\t\t\t\t\tcompare = less_than\n";
	completeEffect += "\t\t\t\t\t}\n";
	completeEffect += "\t\t\t\t}\n";
	completeEffect += "\t\t\t\tset_variable = {\n";
	completeEffect += "\t\t\t\t\tvar = civil_war_size_var\n";
	completeEffect += "\t\t\t\t\tvalue = 0.3\n";
	completeEffect += "\t\t\t\t}\n";
	completeEffect += "\t\t\t}\n";
	completeEffect += "\t\t\tstart_civil_war = {\n";
	completeEffect += "\t\t\t\truling_party = " + decisionIdeology + "\n";
	completeEffect += "\t\t\t\tideology = ROOT\n";
	completeEffect += "\t\t\t\tsize = civil_war_size_var\n";
	completeEffect += "\t\t\t\tkeep_unit_leaders_trigger = {\n";
	completeEffect += "\t\t\t\t\thas_trait = hidden_sympathies\n";
	completeEffect += "\t\t\t\t}\n";
	completeEffect += "\t\t\t}\n";
	completeEffect += "\t\t\tclr_country_flag = preparation_for_" + decisionIdeology + "_civil_war\n";
	completeEffect += "\t\t\tclr_country_flag = military_support_for_" + decisionIdeology + "_civil_war\n";
	completeEffect += "\t\t\tclr_country_flag = civil_support_for_" + decisionIdeology + "_civil_war\n";
	completeEffect += "\t\t\tset_country_flag = ideology_civil_war\n";
	completeEffect += "\t\t}";
	decisionToUpdate.setCompleteEffect(completeEffect);
}


void HoI4::decisionsCategory::updateHoldTheIdeologyNationalReferendum(
	decision& decisionToUpdate,
	const Events& theEvents
) {
	std::string decisionIdeology = decisionToUpdate.getName().substr(9, decisionToUpdate.getName().length());
	decisionIdeology = decisionIdeology.substr(0, decisionIdeology.find_first_of('_'));
	auto eventNumber = theEvents.getEventNumber("fiftyPercent" + decisionIdeology);
	if (eventNumber)
	{
		std::string completeEffect = "= {\n";
		completeEffect += "\t\t\tcountry_event = { id = political." + std::to_string(*eventNumber) + " }\n";
		completeEffect += "\t\t}";
		decisionToUpdate.setCompleteEffect(completeEffect);
	}
}


std::ostream& HoI4::operator<<(std::ostream& outStream, const decisionsCategory& outCategory)
{
	outStream << outCategory.name << " = {\n";
	for (auto decision: outCategory.theDecisions)
	{
		outStream << decision << "\n";
	}
	if (outCategory.theDecisions.size() == 0)
	{
		outStream << "\n";
	}
	outStream << "}\n";
	outStream << "\n";

	return outStream;
}


bool HoI4::decisionsCategory::operator==(const decisionsCategory& otherCategory)
{
	return (name == otherCategory.name);
}