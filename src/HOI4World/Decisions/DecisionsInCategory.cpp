#include "src/HOI4World/Decisions/DecisionsInCategory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/Events/Events.h"

#pragma optimize("", off)

HoI4::DecisionsInCategory::DecisionsInCategory(std::string categoryName, std::istream& theStream):
	 name(std::move(categoryName))
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& decisionName, std::istream& theStream) {
		const decision theDecision(decisionName, theStream);
		theDecisions.push_back(theDecision);
	});

	parseStream(theStream);
}

#pragma optimize("", on)
void updateOpenUpPoliticalDiscourse(HoI4::decision& decisionToUpdate, const std::set<std::string>& majorIdeologies);
void updateDiscreditGovernment(HoI4::decision& decisionToUpdate, const std::set<std::string>& majorIdeologies);
void updateInstitutePressCensorship(HoI4::decision& decisionToUpdate, const std::set<std::string>& majorIdeologies);
void updateIgniteTheIdeologyCivilWar(HoI4::decision& decisionToUpdate, const std::set<std::string>& majorIdeologies);

void HoI4::DecisionsInCategory::updatePoliticalDecisions(const std::set<std::string>& majorIdeologies,
	 const Events& theEvents)
{
	for (auto& theDecision: theDecisions)
	{
		const auto& decisionName = theDecision.getName();
		if (decisionName.starts_with("open_up_political_discourse_"))
		{
			updateOpenUpPoliticalDiscourse(theDecision, majorIdeologies);
		}
		if (decisionName.starts_with("discredit_government_"))
		{
			updateDiscreditGovernment(theDecision, majorIdeologies);
		}
		if (decisionName.starts_with("institute_press_censorship_"))
		{
			updateInstitutePressCensorship(theDecision, majorIdeologies);
		}
		if (decisionName.starts_with("ignite_the_") && (decisionName.find("single_state") == std::string::npos))
		{
			updateIgniteTheIdeologyCivilWar(theDecision, majorIdeologies);
		}
		if (decisionName.starts_with("hold_the_"))
		{
			updateHoldTheIdeologyNationalReferendum(theDecision, theEvents);
		}
	}
}


void updateOpenUpPoliticalDiscourse(HoI4::decision& decisionToUpdate, const std::set<std::string>& majorIdeologies)
{
	std::string available = "= {\n";
	for (const auto& ideology: majorIdeologies)
	{
		available += "\t\t\t" + ideology + " < 0.9\n";
	}
	available += "\t\t}";
	decisionToUpdate.setAvailable(available);
}


void updateDiscreditGovernment(HoI4::decision& decisionToUpdate, const std::set<std::string>& majorIdeologies)
{
	const auto decisionIdeology = decisionToUpdate.getName().substr(21, decisionToUpdate.getName().length());
	std::string available = "= {\n";
	for (const auto& ideology: majorIdeologies)
	{
		available += "\t\t\t" + ideology + " < 0.8\n";
	}
	available += "\t\t\thas_idea_with_trait = " + decisionIdeology + "_minister\n";
	available += "\t\t}";
	decisionToUpdate.setAvailable(available);
	std::string completeEffect = "= {\n";
	completeEffect += "\t\t\tadd_stability = -0.010\n";
	for (const auto& ideology: majorIdeologies)
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


void updateInstitutePressCensorship(HoI4::decision& decisionToUpdate, const std::set<std::string>& majorIdeologies)
{
	auto decisionIdeology = decisionToUpdate.getName().substr(27, decisionToUpdate.getName().length());
	decisionIdeology = decisionIdeology.substr(0, decisionIdeology.find_last_of('_'));
	std::string modifier = "= {\n";
	for (const auto& ideology: majorIdeologies)
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


void updateIgniteTheIdeologyCivilWar(HoI4::decision& decisionToUpdate, const std::set<std::string>& majorIdeologies)
{
	auto decisionIdeology = decisionToUpdate.getName().substr(11, decisionToUpdate.getName().length());
	decisionIdeology = decisionIdeology.substr(0, decisionIdeology.find_first_of('_'));
	std::string completeEffect = "= {\n";
	for (const auto& ideology: majorIdeologies)
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


void HoI4::DecisionsInCategory::updateHoldTheIdeologyNationalReferendum(decision& decisionToUpdate,
	 const Events& theEvents) const
{
	auto decisionIdeology = decisionToUpdate.getName().substr(9, decisionToUpdate.getName().length());
	decisionIdeology = decisionIdeology.substr(0, decisionIdeology.find_first_of('_'));
	auto eventNumber = theEvents.getEventNumber("fiftyPercent" + decisionIdeology);
	if (eventNumber)
	{
		std::string completeEffect = "= {\n";
		completeEffect += "\t\t\tcountry_event = { id = conv.political." + std::to_string(*eventNumber) + " }\n";
		completeEffect += "\t\t}";
		decisionToUpdate.setCompleteEffect(completeEffect);
	}
}


bool HoI4::DecisionsInCategory::operator==(const DecisionsInCategory& otherCategory) const
{
	return (name == otherCategory.name);
}