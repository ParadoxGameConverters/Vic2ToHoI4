#include "ScriptedLocalisations.h"



void HoI4::ScriptedLocalisations::initialize(const std::string& strongestNavyTag, const std::string& secondStrongestNavyTag)
{
	ScriptedLocalisation GetStrengthRatioBritain;
	GetStrengthRatioBritain.setName("GetStrengthRatioBritain");
	std::string text;
	text += "\t\ttrigger = { \n";
	text += "\t\t\tif = { \n";
	text += "\t\t\t\tlimit = { " + strongestNavyTag + " = { has_naval_treaty_trigger = yes } }\n";
	text += "\t\t\t\tnaval_strength_comparison = { \n";
	text += "\t\t\t\t\tother = " + strongestNavyTag + "\n";
	text += "\t\t\t\t\tratio < 1\n";
	text += "\t\t\t\t\tsub_unit_def_weights = { \n";
	text += "\t\t\t\t\t\tcarrier = 0.5\n";
	text += "\t\t\t\t\t\tbattleship = 1\n";
	text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
	text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
	text += "\t\t\t\t\t}\n";
	text += "\t\t\t\t}\n";
	text += "\t\t\t\tnaval_strength_comparison = { \n";
	text += "\t\t\t\t\tother = " + strongestNavyTag + "\n";
	text += "\t\t\t\t\tratio > 0.9\n";
	text += "\t\t\t\t\tsub_unit_def_weights = { \n";
	text += "\t\t\t\t\t\tcarrier = 0.5\n";
	text += "\t\t\t\t\t\tbattleship = 1\n";
	text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
	text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
	text += "\t\t\t\t\t}\n";
	text += "\t\t\t\t}\n";
	text += "\t\t\t}\n";
	text += "\t\t\telse_if = { \n";
	text += "\t\t\t\tlimit = { " + secondStrongestNavyTag + " = { has_naval_treaty_trigger = yes } }\n";
	text += "\t\t\t\tnaval_strength_comparison = { \n";
	text += "\t\t\t\t\tother = " + secondStrongestNavyTag + "\n";
	text += "\t\t\t\t\tratio < 1\n";
	text += "\t\t\t\t\tsub_unit_def_weights = { \n";
	text += "\t\t\t\t\t\tcarrier = 0.5\n";
	text += "\t\t\t\t\t\tbattleship = 1\n";
	text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
	text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
	text += "\t\t\t\t\t}\n";
	text += "\t\t\t\t}\n";
	text += "\t\t\t\tnaval_strength_comparison = { \n";
	text += "\t\t\t\t\tother = " + secondStrongestNavyTag + "\n";
	text += "\t\t\t\t\tratio > 0.9\n";
	text += "\t\t\t\t\tsub_unit_def_weights = { \n";
	text += "\t\t\t\t\t\tcarrier = 0.5\n";
	text += "\t\t\t\t\t\tbattleship = 1\n";
	text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
	text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
	text += "\t\t\t\t\t}\n";
	text += "\t\t\t\t}\n";
	text += "\t\t\t}\n";
	text += "\t\t}\n";
	text += "\t\tlocalization_key = Naval_treaty_90\n";
	GetStrengthRatioBritain.addText(text);

	text = "\t\ttrigger = { \n";
	text += "\t\t\tif = { \n";
	text += "\t\t\t\tlimit = { " + strongestNavyTag + " = { has_naval_treaty_trigger = yes } }\n";
	text += "\t\t\t\tnaval_strength_comparison = { \n";
	text += "\t\t\t\t\tother = " + strongestNavyTag + "\n";
	text += "\t\t\t\t\tratio < 0.9\n";
	text += "\t\t\t\t\tsub_unit_def_weights = { \n";
	text += "\t\t\t\t\t\tcarrier = 0.5\n";
	text += "\t\t\t\t\t\tbattleship = 1\n";
	text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
	text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
	text += "\t\t\t\t\t}\n";
	text += "\t\t\t\t}\n";
	text += "\t\t\t\tnaval_strength_comparison = { \n";
	text += "\t\t\t\t\tother = " + strongestNavyTag + "\n";
	text += "\t\t\t\t\tratio > 0.75\n";
	text += "\t\t\t\t\tsub_unit_def_weights = { \n";
	text += "\t\t\t\t\t\tcarrier = 0.5\n";
	text += "\t\t\t\t\t\tbattleship = 1\n";
	text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
	text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
	text += "\t\t\t\t\t}\n";
	text += "\t\t\t\t}\n";
	text += "\t\t\t}\n";
	text += "\t\t\telse_if = { \n";
	text += "\t\t\t\tlimit = { " + secondStrongestNavyTag + " = { has_naval_treaty_trigger = yes } }\n";
	text += "\t\t\t\tnaval_strength_comparison = { \n";
	text += "\t\t\t\t\tother = " + secondStrongestNavyTag + "\n";
	text += "\t\t\t\t\tratio < 0.9\n";
	text += "\t\t\t\t\tsub_unit_def_weights = { \n";
	text += "\t\t\t\t\t\tcarrier = 0.5\n";
	text += "\t\t\t\t\t\tbattleship = 1\n";
	text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
	text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
	text += "\t\t\t\t\t}\n";
	text += "\t\t\t\t}\n";
	text += "\t\t\t\tnaval_strength_comparison = { \n";
	text += "\t\t\t\t\tother = " + secondStrongestNavyTag + "\n";
	text += "\t\t\t\t\tratio > 0.75\n";
	text += "\t\t\t\t\tsub_unit_def_weights = { \n";
	text += "\t\t\t\t\t\tcarrier = 0.5\n";
	text += "\t\t\t\t\t\tbattleship = 1\n";
	text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
	text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
	text += "\t\t\t\t\t}\n";
	text += "\t\t\t\t}\n";
	text += "\t\t\t}\n";
	text += "\t\t}\n";
	text += "\t\tlocalization_key = Naval_treaty_75\n";
	GetStrengthRatioBritain.addText(text);

	text = "\t\ttrigger = { \n";
	text += "\t\t\tif = { \n";
	text += "\t\t\t\tlimit = { " + strongestNavyTag + " = { has_naval_treaty_trigger = yes } }\n";
	text += "\t\t\t\tnaval_strength_comparison = { \n";
	text += "\t\t\t\t\tother = " + strongestNavyTag + "\n";
	text += "\t\t\t\t\tratio < 0.75\n";
	text += "\t\t\t\t\tsub_unit_def_weights = { \n";
	text += "\t\t\t\t\t\tcarrier = 0.5\n";
	text += "\t\t\t\t\t\tbattleship = 1\n";
	text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
	text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
	text += "\t\t\t\t\t}\n";
	text += "\t\t\t\t}\n";
	text += "\t\t\t\tnaval_strength_comparison = { \n";
	text += "\t\t\t\t\tother = " + strongestNavyTag + "\n";
	text += "\t\t\t\t\tratio > 0.5\n";
	text += "\t\t\t\t\tsub_unit_def_weights = { \n";
	text += "\t\t\t\t\t\tcarrier = 0.5\n";
	text += "\t\t\t\t\t\tbattleship = 1\n";
	text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
	text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
	text += "\t\t\t\t\t}\n";
	text += "\t\t\t\t}\n";
	text += "\t\t\t}\n";
	text += "\t\t\telse_if = { \n";
	text += "\t\t\t\tlimit = { " + secondStrongestNavyTag + " = { has_naval_treaty_trigger = yes } }\n";
	text += "\t\t\t\tnaval_strength_comparison = { \n";
	text += "\t\t\t\t\tother = " + secondStrongestNavyTag + "\n";
	text += "\t\t\t\t\tratio < 0.75\n";
	text += "\t\t\t\t\tsub_unit_def_weights = { \n";
	text += "\t\t\t\t\t\tcarrier = 0.5\n";
	text += "\t\t\t\t\t\tbattleship = 1\n";
	text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
	text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
	text += "\t\t\t\t\t}\n";
	text += "\t\t\t\t}\n";
	text += "\t\t\t\tnaval_strength_comparison = { \n";
	text += "\t\t\t\t\tother = " + secondStrongestNavyTag + "\n";
	text += "\t\t\t\t\tratio > 0.5\n";
	text += "\t\t\t\t\tsub_unit_def_weights = { \n";
	text += "\t\t\t\t\t\tcarrier = 0.5\n";
	text += "\t\t\t\t\t\tbattleship = 1\n";
	text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
	text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
	text += "\t\t\t\t\t}\n";
	text += "\t\t\t\t}\n";
	text += "\t\t\t}\n";
	text += "\t\t}\n";
	text += "\t\tlocalization_key = Naval_treaty_50\n";
	GetStrengthRatioBritain.addText(text);

	text = "\t\ttrigger = { \n";
	text += "\t\t\tif = { \n";
	text += "\t\t\t\tlimit = { " + strongestNavyTag + " = { has_naval_treaty_trigger = yes } }\n";
	text += "\t\t\t\tnaval_strength_comparison = { \n";
	text += "\t\t\t\t\tother = " + strongestNavyTag + "\n";
	text += "\t\t\t\t\tratio < 0.5\n";
	text += "\t\t\t\t\tsub_unit_def_weights = { \n";
	text += "\t\t\t\t\t\tcarrier = 0.5\n";
	text += "\t\t\t\t\t\tbattleship = 1\n";
	text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
	text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
	text += "\t\t\t\t\t}\n";
	text += "\t\t\t\t}\n";
	text += "\t\t\t}\n";
	text += "\t\t\telse_if = { \n";
	text += "\t\t\t\tlimit = { " + secondStrongestNavyTag + " = { has_naval_treaty_trigger = yes } }\n";
	text += "\t\t\t\tnaval_strength_comparison = { \n";
	text += "\t\t\t\t\tother = " + secondStrongestNavyTag + "\n";
	text += "\t\t\t\t\tratio < 0.5\n";
	text += "\t\t\t\t\tsub_unit_def_weights = { \n";
	text += "\t\t\t\t\t\tcarrier = 0.5\n";
	text += "\t\t\t\t\t\tbattleship = 1\n";
	text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
	text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
	text += "\t\t\t\t\t}\n";
	text += "\t\t\t\t}\n";
	text += "\t\t\t}\n";
	text += "\t\t}\n";
	text += "\t\tlocalization_key = Naval_treaty_lower_than_50\n";
	GetStrengthRatioBritain.addText(text);

	text = "\t\ttrigger = { \n";
	text += "\t\t\tif = { \n";
	text += "\t\t\t\tlimit = { " + strongestNavyTag + " = { has_naval_treaty_trigger = yes } }\n";
	text += "\t\t\t\tnaval_strength_comparison = { \n";
	text += "\t\t\t\t\tother = " + strongestNavyTag + "\n";
	text += "\t\t\t\t\tratio > 1\n";
	text += "\t\t\t\t\tsub_unit_def_weights = { \n";
	text += "\t\t\t\t\t\tcarrier = 0.5\n";
	text += "\t\t\t\t\t\tbattleship = 1\n";
	text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
	text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
	text += "\t\t\t\t\t}\n";
	text += "\t\t\t\t}\n";
	text += "\t\t\t}\n";
	text += "\t\t\telse_if = { \n";
	text += "\t\t\t\tlimit = { " + secondStrongestNavyTag + " = { has_naval_treaty_trigger = yes } }\n";
	text += "\t\t\t\tnaval_strength_comparison = { \n";
	text += "\t\t\t\t\tother = " + secondStrongestNavyTag + "\n";
	text += "\t\t\t\t\tratio > 1\n";
	text += "\t\t\t\t\tsub_unit_def_weights = { \n";
	text += "\t\t\t\t\t\tcarrier = 0.5\n";
	text += "\t\t\t\t\t\tbattleship = 1\n";
	text += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
	text += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
	text += "\t\t\t\t\t}\n";
	text += "\t\t\t\t}\n";
	text += "\t\t\t}\n";
	text += "\t\t}\n";
	text += "\t\tlocalization_key = Naval_treaty_over_100\n";
	GetStrengthRatioBritain.addText(text);
	scriptedLocalisations.push_back(GetStrengthRatioBritain);

	ScriptedLocalisation GetRelevantNavalTreatyNation;
	GetRelevantNavalTreatyNation.setName("GetRelevantNavalTreatyNation");
	text = "\t\ttrigger = { \n";
	text += "\t\t\t" + strongestNavyTag + " = { \n";
	text += "\t\t\t\thas_naval_treaty_trigger = yes\n";
	text += "\t\t\t}\n";
	text += "\t\t}\n";
	text += "\t\tlocalization_key = " + strongestNavyTag + "_Naval_treaty_nation\n";
	GetRelevantNavalTreatyNation.addText(text);

	text = "\t\ttrigger = { \n";
	text += "\t\t\t" + strongestNavyTag + " = { \n";
	text += "\t\t\t\tnot = { has_naval_treaty_trigger = yes }\n";
	text += "\t\t\t}\n";
	text += "\t\t\t" + secondStrongestNavyTag + " = { \n";
	text += "\t\t\t\thas_naval_treaty_trigger = yes\n";
	text += "\t\t\t}\n";
	text += "\t\t}\n";
	text += "\t\tlocalization_key = " + secondStrongestNavyTag + "_Naval_treaty_nation\n";
	GetRelevantNavalTreatyNation.addText(text);
	scriptedLocalisations.push_back(GetRelevantNavalTreatyNation);
}


void HoI4::ScriptedLocalisations::giveAdjectiveLocalisation(
	const std::string& language,
	ScriptedLocalisation&& localisation
)
{
	if (
		auto& languageAdjectives = adjectiveLocalisations.find(language);
		languageAdjectives != adjectiveLocalisations.end()
		)
	{
		languageAdjectives->second.push_back(localisation);
	}
	else
	{
		std::vector<ScriptedLocalisation> localisations{ localisation };
		adjectiveLocalisations.insert(std::make_pair(language, localisations));
	}
}