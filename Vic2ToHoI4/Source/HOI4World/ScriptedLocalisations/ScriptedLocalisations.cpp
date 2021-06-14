#include "ScriptedLocalisations.h"
#include <regex>



std::string createNavyScriptedLocalisationsText(const std::vector<std::string>& strongestNaviesTags,
	 const std::string& upperRatio,
	 const std::string& lowerRatio,
	 const std::string& localisationLevel)
{
	std::string text;
	text += "= {\n";
	text += "\t\ttrigger = { \n";
	text += "\t\t\tif = { \n";
	text += "\t\t\t\tlimit = { " + strongestNaviesTags[0] + " = { has_naval_treaty_trigger = yes } }\n";
	text += "\t\t\t\tnaval_strength_comparison = { \n";
	text += "\t\t\t\t\tother = " + strongestNaviesTags[0] + "\n";
	text += "\t\t\t\t\tratio < " + upperRatio + "\n";
	text += "\t\t\t\t\tsub_unit_def_weights = { \n";
	text += "\t\t\t\t\t\tcarrier = 0.5\n";
	text += "\t\t\t\t\t\tbattleship = 1\n";
	text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
	text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
	text += "\t\t\t\t\t}\n";
	text += "\t\t\t\t}\n";
	text += "\t\t\t\tnaval_strength_comparison = { \n";
	text += "\t\t\t\t\tother = " + strongestNaviesTags[0] + "\n";
	text += "\t\t\t\t\tratio > " + lowerRatio + "\n";
	text += "\t\t\t\t\tsub_unit_def_weights = { \n";
	text += "\t\t\t\t\t\tcarrier = 0.5\n";
	text += "\t\t\t\t\t\tbattleship = 1\n";
	text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
	text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
	text += "\t\t\t\t\t}\n";
	text += "\t\t\t\t}\n";
	text += "\t\t\t}\n";
	for (size_t i = 1; i < strongestNaviesTags.size(); i++)
	{
		text += "\t\t\telse_if = { \n";
		text += "\t\t\t\tlimit = { " + strongestNaviesTags[i] + " = { has_naval_treaty_trigger = yes } }\n";
		text += "\t\t\t\tnaval_strength_comparison = { \n";
		text += "\t\t\t\t\tother = " + strongestNaviesTags[i] + "\n";
		text += "\t\t\t\t\tratio < " + upperRatio + "\n";
		text += "\t\t\t\t\tsub_unit_def_weights = { \n";
		text += "\t\t\t\t\t\tcarrier = 0.5\n";
		text += "\t\t\t\t\t\tbattleship = 1\n";
		text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
		text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
		text += "\t\t\t\t\t}\n";
		text += "\t\t\t\t}\n";
		text += "\t\t\t\tnaval_strength_comparison = { \n";
		text += "\t\t\t\t\tother = " + strongestNaviesTags[i] + "\n";
		text += "\t\t\t\t\tratio > " + lowerRatio + "\n";
		text += "\t\t\t\t\tsub_unit_def_weights = { \n";
		text += "\t\t\t\t\t\tcarrier = 0.5\n";
		text += "\t\t\t\t\t\tbattleship = 1\n";
		text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
		text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
		text += "\t\t\t\t\t}\n";
		text += "\t\t\t\t}\n";
		text += "\t\t\t}\n";
	}
	text += "\t\t}\n";
	text += "\t\tlocalization_key = Naval_treaty_" + localisationLevel + "\n";
	text += "\t}";

	return text;
}


void HoI4::ScriptedLocalisations::addNavyScriptedLocalisations(const std::vector<std::string>& strongestNaviesTags)
{
	ScriptedLocalisation GetStrengthRatioBritain;
	GetStrengthRatioBritain.setName("GetStrengthRatioBritain");
	GetStrengthRatioBritain.addText(createNavyScriptedLocalisationsText(strongestNaviesTags, "1", "0.9", "90"));
	GetStrengthRatioBritain.addText(createNavyScriptedLocalisationsText(strongestNaviesTags, "0.9", "0.75", "75"));
	GetStrengthRatioBritain.addText(createNavyScriptedLocalisationsText(strongestNaviesTags, "0.75", "0.5", "50"));

	std::string text = "= {\n";
	text += "\t\ttrigger = { \n";
	text += "\t\t\tif = { \n";
	text += "\t\t\t\tlimit = { " + strongestNaviesTags[0] + " = { has_naval_treaty_trigger = yes } }\n";
	text += "\t\t\t\tnaval_strength_comparison = { \n";
	text += "\t\t\t\t\tother = " + strongestNaviesTags[0] + "\n";
	text += "\t\t\t\t\tratio < 0.5\n";
	text += "\t\t\t\t\tsub_unit_def_weights = { \n";
	text += "\t\t\t\t\t\tcarrier = 0.5\n";
	text += "\t\t\t\t\t\tbattleship = 1\n";
	text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
	text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
	text += "\t\t\t\t\t}\n";
	text += "\t\t\t\t}\n";
	text += "\t\t\t}\n";
	for (size_t i = 1; i < strongestNaviesTags.size(); i++)
	{
		text += "\t\t\telse_if = { \n";
		text += "\t\t\t\tlimit = { " + strongestNaviesTags[i] + " = { has_naval_treaty_trigger = yes } }\n";
		text += "\t\t\t\tnaval_strength_comparison = { \n";
		text += "\t\t\t\t\tother = " + strongestNaviesTags[i] + "\n";
		text += "\t\t\t\t\tratio < 0.5\n";
		text += "\t\t\t\t\tsub_unit_def_weights = { \n";
		text += "\t\t\t\t\t\tcarrier = 0.5\n";
		text += "\t\t\t\t\t\tbattleship = 1\n";
		text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
		text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
		text += "\t\t\t\t\t}\n";
		text += "\t\t\t\t}\n";
		text += "\t\t\t}\n";
	}
	text += "\t\t}\n";
	text += "\t\tlocalization_key = Naval_treaty_lower_than_50\n";
	text += "\t}";
	GetStrengthRatioBritain.addText(text);

	text = "= {\n";
	text += "\t\ttrigger = { \n";
	text += "\t\t\tif = { \n";
	text += "\t\t\t\tlimit = { " + strongestNaviesTags[0] + " = { has_naval_treaty_trigger = yes } }\n";
	text += "\t\t\t\tnaval_strength_comparison = { \n";
	text += "\t\t\t\t\tother = " + strongestNaviesTags[0] + "\n";
	text += "\t\t\t\t\tratio > 1\n";
	text += "\t\t\t\t\tsub_unit_def_weights = { \n";
	text += "\t\t\t\t\t\tcarrier = 0.5\n";
	text += "\t\t\t\t\t\tbattleship = 1\n";
	text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
	text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
	text += "\t\t\t\t\t}\n";
	text += "\t\t\t\t}\n";
	text += "\t\t\t}\n";
	for (size_t i = 1; i < strongestNaviesTags.size(); i++)
	{
		text += "\t\t\telse_if = { \n";
		text += "\t\t\t\tlimit = { " + strongestNaviesTags[i] + " = { has_naval_treaty_trigger = yes } }\n";
		text += "\t\t\t\tnaval_strength_comparison = { \n";
		text += "\t\t\t\t\tother = " + strongestNaviesTags[i] + "\n";
		text += "\t\t\t\t\tratio > 1\n";
		text += "\t\t\t\t\tsub_unit_def_weights = { \n";
		text += "\t\t\t\t\t\tcarrier = 0.5\n";
		text += "\t\t\t\t\t\tbattleship = 1\n";
		text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
		text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
		text += "\t\t\t\t\t}\n";
		text += "\t\t\t\t}\n";
		text += "\t\t\t}\n";
	}
	text += "\t\t}\n";
	text += "\t\tlocalization_key = Naval_treaty_over_100\n";
	text += "\t}";
	GetStrengthRatioBritain.addText(text);
	scriptedLocalisations.push_back(GetStrengthRatioBritain);

	ScriptedLocalisation GetRelevantNavalTreatyNation;
	GetRelevantNavalTreatyNation.setName("GetRelevantNavalTreatyNation");
	text = "= {\n";
	text += "\t\ttrigger = { \n";
	text += "\t\t\t" + strongestNaviesTags[0] + " = { \n";
	text += "\t\t\t\thas_naval_treaty_trigger = yes\n";
	text += "\t\t\t}\n";
	text += "\t\t}\n";
	text += "\t\tlocalization_key = " + strongestNaviesTags[0] + "_Naval_treaty_nation\n";
	text += "\t}";
	GetRelevantNavalTreatyNation.addText(text);

	std::vector<std::string> addedKeyTags{strongestNaviesTags[0]};
	for (size_t i = 1; i < strongestNaviesTags.size(); i++)
	{
		text = "= {\n";
		text += "\t\ttrigger = { \n";
		for (const auto& addedKeyTag: addedKeyTags)
		{
			text += "\t\t\t" + addedKeyTag + " = { \n";
			text += "\t\t\t\tnot = { has_naval_treaty_trigger = yes }\n";
			text += "\t\t\t}\n";
		}
		text += "\t\t\t" + strongestNaviesTags[i] + " = { \n";
		text += "\t\t\t\thas_naval_treaty_trigger = yes\n";
		text += "\t\t\t}\n";
		text += "\t\t}\n";
		text += "\t\tlocalization_key = " + strongestNaviesTags[i] + "_Naval_treaty_nation\n";
		text += "\t}";
		GetRelevantNavalTreatyNation.addText(text);

		addedKeyTags.push_back(strongestNaviesTags[i]);
	}

	scriptedLocalisations.push_back(GetRelevantNavalTreatyNation);
}


void HoI4::ScriptedLocalisations::giveAdjectiveLocalisation(const std::string& language,
	 ScriptedLocalisation&& localisation)
{
	if (auto languageAdjectives = adjectiveLocalisations.find(language);
		 languageAdjectives != adjectiveLocalisations.end())
	{
		languageAdjectives->second.push_back(localisation);
	}
	else
	{
		std::vector<ScriptedLocalisation> localisations{localisation};
		adjectiveLocalisations.emplace(std::make_pair(language, localisations));
	}
}


void HoI4::ScriptedLocalisations::filterIdeologyLocalisations(const std::set<std::string>& majorIdeologies)
{
	for (auto& localisation: ideologyLocalisations)
	{
		localisation.filterTexts([majorIdeologies](const std::string& text) {
			std::smatch match;
			for (const auto& ideology: majorIdeologies)
			{
				if (std::regex_search(text, match, std::regex(ideology)))
				{
					return false;
				}
			}
			return true;
		});
	}
}


void HoI4::ScriptedLocalisations::updateIdeologyLocalisations(const std::set<std::string>& majorIdeologies)
{
	std::string fascismReplacement;
	if (majorIdeologies.contains("fascism"))
	{
		fascismReplacement = "\n\t\t\t\thas_government = fascism";
	}
	std::string communismReplacement;
	if (majorIdeologies.contains("communism"))
	{
		communismReplacement = "\n\t\t\t\thas_government = communism";
	}
	std::string radicalReplacement;
	if (majorIdeologies.contains("radical"))
	{
		radicalReplacement = "\n\t\t\t\thas_government = radical";
	}
	std::string absolutistReplacement;
	if (majorIdeologies.contains("absolutist"))
	{
		absolutistReplacement = "\n\t\t\t\thas_government = absolutist";
	}
	std::string democraticReplacement;
	if (majorIdeologies.contains("democratic"))
	{
		democraticReplacement = "\n\t\t\t\thas_government = democratic";
	}

	for (auto& localisation: ideologyLocalisations)
	{
		localisation.updateTexts(std::regex("\n.*FASCISM_PLACEHOLDER"), fascismReplacement);
		localisation.updateTexts(std::regex("\n.*COMMUNISM_PLACEHOLDER"), communismReplacement);
		localisation.updateTexts(std::regex("\n.*RADICAL_PLACEHOLDER"), radicalReplacement);
		localisation.updateTexts(std::regex("\n.*ABSOLUTIST_PLACEHOLDER"), absolutistReplacement);
		localisation.updateTexts(std::regex("\n.*DEMOCRATIC_PLACEHOLDER"), democraticReplacement);
	}
}