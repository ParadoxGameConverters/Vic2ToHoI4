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
	registerKeyword(std::regex("[A-Za-z0-9\\_]+"), [this](const std::string& decisionName, std::istream& theStream)
	{
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
			std::string available = "= {\n";
			for (auto ideology : majorIdeologies)
			{
				available += "			" + ideology + " < 0.9\n";
			}
			available += "		}";
			theDecision.setAvailable(available);
		}
		if (theDecision.getName().substr(0, 21) == "discredit_government_")
		{
			std::string decisionIdeology = theDecision.getName().substr(21, theDecision.getName().length());
			std::string available = "= {\n";
			for (auto ideology : majorIdeologies)
			{
				available += "			" + ideology + " < 0.8\n";
			}
			available += "			has_idea_with_trait = " + decisionIdeology + "_minister\n";
			available += "		}";
			theDecision.setAvailable(available);
			std::string completeEffect = "= {\n";
			completeEffect += "			add_stability = -0.010\n";
			for (auto ideology : majorIdeologies)
			{
				if (ideology == decisionIdeology)
				{
					continue;
				}
				completeEffect += "			if = {\n";
				completeEffect += "				limit = {\n";
				completeEffect += "					has_government = " + ideology + "\n";
				completeEffect += "				}\n";
				completeEffect += "				add_popularity = {\n";
				completeEffect += "					ideology = " + ideology + "\n";
				completeEffect += "					popularity = -0.1\n";
				completeEffect += "				}\n";
				completeEffect += "			}\n";
			}
			completeEffect += "		}";
			theDecision.setCompleteEffect(completeEffect);
		}
		if (theDecision.getName().substr(0, 27) == "institute_press_censorship_")
		{
			std::string decisionIdeology = theDecision.getName().substr(27, theDecision.getName().length());
			decisionIdeology = decisionIdeology.substr(0, decisionIdeology.find_last_of('_'));
			std::string modifier = "= {\n";
			for (auto ideology : majorIdeologies)
			{
				if (ideology == decisionIdeology)
				{
					modifier += "			" + ideology + "_drift = 0.03\n";
				}
				else
				{
					modifier += "			" + ideology + "_drift = -0.01\n";
				}
			}
			modifier += "		}";
			theDecision.setModifier(modifier);
		}
		if (theDecision.getName().substr(0, 11) == "ignite_the_")
		{
			std::string decisionIdeology = theDecision.getName().substr(11, theDecision.getName().length());
			decisionIdeology = decisionIdeology.substr(0, decisionIdeology.find_first_of('_'));
			std::string completeEffect = "= {\n";
			for (auto ideology : majorIdeologies)
			{
				if (ideology == decisionIdeology)
				{
					continue;
				}
				completeEffect += "			if = {\n";
				completeEffect += "				limit = {\n";
				completeEffect += "					has_government = " + ideology + "\n";
				completeEffect += "				}\n";
				completeEffect += "				set_variable = {\n";
				completeEffect += "					var = civil_war_size_var\n";
				completeEffect += "					value = party_popularity@" + ideology + "\n";
				completeEffect += "				}\n";
				completeEffect += "			}\n";
			}
			completeEffect += "			subtract_from_variable = {\n";
			completeEffect += "				var = civil_war_size_var\n";
			completeEffect += "				value = army_support_var\n";
			completeEffect += "			}\n";
			completeEffect += "			if = {\n";
			completeEffect += "				limit = {\n";
			completeEffect += "					check_variable = {\n";
			completeEffect += "						var = civil_war_size_var\n";
			completeEffect += "						value = 0.3\n";
			completeEffect += "						compare = less_than\n";
			completeEffect += "					}\n";
			completeEffect += "				}\n";
			completeEffect += "				set_variable = {\n";
			completeEffect += "					var = civil_war_size_var\n";
			completeEffect += "					value = 0.3\n";
			completeEffect += "				}\n";
			completeEffect += "			}\n";
			completeEffect += "			start_civil_war = {\n";
			completeEffect += "				ruling_party = " + decisionIdeology + "\n";
			completeEffect += "				ideology = ROOT\n";
			completeEffect += "				size = civil_war_size_var\n";
			completeEffect += "				keep_unit_leaders_trigger = {\n";
			completeEffect += "					has_trait = hidden_sympathies\n";
			completeEffect += "				}\n";
			completeEffect += "			}\n";
			completeEffect += "			clr_country_flag = preparation_for_" + decisionIdeology + "_civil_war\n";
			completeEffect += "			clr_country_flag = military_support_for_" + decisionIdeology + "_civil_war\n";
			completeEffect += "			clr_country_flag = civil_support_for_" + decisionIdeology + "_civil_war\n";
			completeEffect += "			set_country_flag = ideology_civil_war\n";
			completeEffect += "		}";
			theDecision.setCompleteEffect(completeEffect);
		}
		if (theDecision.getName().substr(0, 9) == "hold_the_")
		{
			std::string decisionIdeology = theDecision.getName().substr(9, theDecision.getName().length());
			decisionIdeology = decisionIdeology.substr(0, decisionIdeology.find_first_of('_'));
			auto eventNumber = theEvents.getEventNumber("fiftyPercent" + decisionIdeology);
			if (eventNumber)
			{
				std::string completeEffect = "= {\n";
				completeEffect += "			country_event = { id = political." + std::to_string(*eventNumber) + " }\n";
				completeEffect += "		}";
				theDecision.setCompleteEffect(completeEffect);
			}
		}
	}
}


std::ostream& HoI4::operator<<(std::ostream& outStream, const decisionsCategory& outCategory)
{
	outStream << outCategory.name << " = {\n";
	std::for_each(
		outCategory.theDecisions.begin(),
		outCategory.theDecisions.end(),
		[&outStream](auto decision) { outStream << decision << "\n"; }
	);
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