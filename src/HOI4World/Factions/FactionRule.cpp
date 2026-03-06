#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Parser.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/Factions/FactionRules.h"



HoI4::FactionRule::FactionRule(const std::string& id, std::istream& theStream): id(std::move(id))
{
	registerKeyword("type", [this](std::istream& theStream) {
		type = commonItems::getString(theStream);
	});
	registerKeyword("visible", [this](std::istream& theStream) {
		visible = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("available", [this](std::istream& theStream) {
		available = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("can_remove", [this](std::istream& theStream) {
		canRemove = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("trigger", [this](std::istream& theStream) {
		trigger = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("dismiss_member_trigger", [this](std::istream& theStream) {
		dismissMemberTrigger = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("government_in_exile_allowed_trigger", [this](std::istream& theStream) {
		governmentInExileAllowedTrigger = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("peace_action_modifiers", [this](std::istream& theStream) {
		peaceActionModifiers = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("modifier", [this](std::istream& theStream) {
		modifier = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("effect", [this](std::istream& theStream) {
		effect = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("ai_will_do", [this](std::istream& theStream) {
		aiWillDo = commonItems::stringOfItem(theStream).getString();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
	parseStream(theStream);
	clearRegisteredKeywords();
}

bool HoI4::FactionRule::operator==(const FactionRule& other) const
{
	return id == other.id && type == other.type && visible == other.visible && available == other.available &&
			 canRemove == other.canRemove && trigger == other.trigger &&
			 dismissMemberTrigger == other.dismissMemberTrigger &&
			 governmentInExileAllowedTrigger == other.governmentInExileAllowedTrigger &&
			 peaceActionModifiers == other.peaceActionModifiers && modifier == other.modifier && effect == other.effect &&
			 aiWillDo == other.aiWillDo;
}


void HoI4::FactionRule::updateRule(const std::string& ideology, const std::set<std::string>& majorIdeologies)
{
	if (id == "call_to_war_rule_faction_leader_only")
	{
		std::string aiWillDoStr = "= {\n";
		aiWillDoStr += "\t\tbase = 0\n";
		aiWillDoStr += "\t\tmodifier = { \n";
		aiWillDoStr += "\t\t\tadd = 2\n";
		aiWillDoStr += "\t\t\tis_faction_leader = yes\n";
		if (majorIdeologies.contains("democratic"))
		{
			aiWillDoStr += "\t\t\tNOT = { has_government = democratic }\n";
		}
		aiWillDoStr += "\t\t}\n";
		aiWillDoStr += "\t}\n";
		setAiWillDo(aiWillDoStr);
	}

	if (id == "guarantee_threat_reduction_15")
	{
		std::string aiWillDoStr = "= {\n";
		aiWillDoStr += "\t\tbase = 0\n";
		aiWillDoStr += "\t\tmodifier = { \n";
		aiWillDoStr += "\t\t\tadd = 2\n";
		if (majorIdeologies.contains("democratic"))
		{
			aiWillDoStr += "\t\t\thas_government = democratic\n";
		}
		aiWillDoStr += "\t\t}\n";
		aiWillDoStr += "\t}\n";
		setAiWillDo(aiWillDoStr);
	}

	if (id == "change_leader_rule_never")
	{
		std::string aiWillDoStr = "= {\n";
		aiWillDoStr += "\t\tbase = 0\n";
		aiWillDoStr += "\t\tmodifier = {  \n";
		aiWillDoStr += "\t\t\tadd = 5\n";
		if (majorIdeologies.contains("fascism"))
		{
			aiWillDoStr += "\t\t\thas_government = fascism\n";
		}
		aiWillDoStr += "\t\t\tis_faction_leader = yes \n";
		aiWillDoStr += "\t\t}\n";
		aiWillDoStr += "\t}\n";
		setAiWillDo(aiWillDoStr);
	}

	if (id == "dismissal_rule_world_tension")
	{
		std::string aiWillDoStr = "= {\n";
		aiWillDoStr += "\t\tbase = 0\n";
		aiWillDoStr += "\t\tmodifier = {  \n";
		aiWillDoStr += "\t\t\tadd = 1\n";
		if (majorIdeologies.contains("democratic"))
		{
			aiWillDoStr += "\t\t\thas_government = democratic\n";
		}
		aiWillDoStr += "\t\t\tis_faction_leader = yes \n";
		aiWillDoStr += "\t\t}\n";
		aiWillDoStr += "\t}\n";
		setAiWillDo(aiWillDoStr);
	}

	const std::map<std::string, std::string>& ideologyAdjMap = {{"democratic", "democratic"},
		 {"communism", "communist"},
		 {"fascism", "fasist"},
		 {"radical", "radical"},
		 {"absolutist", "absolutist"},
		 {"neutrality", "unaligned"}};

	const std::vector<std::string>& evilIdeologiesSorted = {"fascism", "communism", "radical", "absolutist"};

	const auto& ideologyAdj = ideologyAdjMap.at(ideology);
	if (id == "joining_rule_non_" + ideologyAdj)
	{
		std::string aiWillDoStr = "= {\n";
		aiWillDoStr += "\t\tbase = 0\n";
		aiWillDoStr += "\t\tmodifier = {\n";
		aiWillDoStr += "\t\t\tadd = 1\n";
		aiWillDoStr += "\t\t\tNOT = { has_government = " + ideology + " }\n";
		aiWillDoStr += "\t\t}\n";
		for (const auto& evilIdeology: evilIdeologiesSorted)
		{
			if (ideology != evilIdeology && majorIdeologies.contains(evilIdeology))
			{
				aiWillDoStr += "\t\tmodifier = {\n";
				aiWillDoStr += "\t\t\tadd = 1\n";
				aiWillDoStr += "\t\t\thas_government = " + evilIdeology + "\n";
				aiWillDoStr += "\t\t}\n";
				break;
			}
		}
		aiWillDoStr += "\t}\n";
		setAiWillDo(aiWillDoStr);
	}

	if (id == "joining_rule_has_no_offensive_war")
	{
		std::string aiWillDoStr = "= {\n";
		aiWillDoStr += "\t\tbase = 0\n";
		aiWillDoStr += "\t\tmodifier = {\n";
		aiWillDoStr += "\t\t\tadd = 2\n";
		aiWillDoStr += "\t\t\tOR = {\n";
		if (majorIdeologies.contains("democratic"))
		{
			aiWillDoStr += "\t\t\t\thas_government = democratic\n";
		}
		aiWillDoStr += "\t\t\t\thas_government = neutrality\n";
		aiWillDoStr += "\t\t\t}\n";
		aiWillDoStr += "\t\t}\n";
		aiWillDoStr += "\t}\n";
		setAiWillDo(aiWillDoStr);
	}

	if (id == "faction_peace_rule_puppeting_focus")
	{
		std::string aiWillDoStr = "= {\n";
		aiWillDoStr += "\t\tbase = 0\n";
		if (majorIdeologies.contains("communism"))
		{
			aiWillDoStr += "\t\tmodifier = {\n";
			aiWillDoStr += "\t\t\tadd = 1\n";
			aiWillDoStr += "\t\t\thas_government = communism\n";
			aiWillDoStr += "\t\t}\n";
		}
		aiWillDoStr += "\t}\n";
		setAiWillDo(aiWillDoStr);
	}

	if (id == "faction_peace_rule_liberation_focus")
	{
		std::string aiWillDoStr = "= {\n";
		aiWillDoStr += "\t\tbase = 0\n";
		if (majorIdeologies.contains("democratic"))
		{
			aiWillDoStr += "\t\tmodifier = {\n";
			aiWillDoStr += "\t\t\tadd = 1\n";
			aiWillDoStr += "\t\t\thas_government = democratic\n";
			aiWillDoStr += "\t\t}\n";
		}
		aiWillDoStr += "\t}\n";
		setAiWillDo(aiWillDoStr);
	}

	if (id == "faction_peace_rule_conquest_focus")
	{
		std::string aiWillDoStr = "= {\n";
		aiWillDoStr += "\t\tbase = 0\n";
		if (majorIdeologies.contains("fascism"))
		{
			aiWillDoStr += "\t\tmodifier = {\n";
			aiWillDoStr += "\t\t\tadd = 2\n";
			aiWillDoStr += "\t\t\thas_government = fascism\n";
			aiWillDoStr += "\t\t}\n";
		}
		aiWillDoStr += "\t}\n";
		setAiWillDo(aiWillDoStr);
	}
}