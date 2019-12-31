#include "Decisions.h"
#include "Decision.h"
#include "../Events.h"
#include <sstream>
#include <regex>



HoI4::decisions::decisions(const Configuration& theConfiguration)
{
	std::ifstream stabilityWarSupportFile(
		theConfiguration.getHoI4Path() + "/common/decisions/stability_war_support.txt"
	);
	if (!stabilityWarSupportFile.is_open())
	{
		throw std::runtime_error(
			"Could not open " + theConfiguration.getHoI4Path() + "/common/decisions/stability_war_support.txt"
		);
	}
	stabilityDecisions.importDecisions(stabilityWarSupportFile);
	stabilityWarSupportFile.close();

	registerKeyword(std::regex("[A-Za-z\\_]+"), [this](const std::string& unused, std::istream& theStream)
	{
		const IdeologicalDecisions ideologicalDecisions(theStream);
		allIdeologicalDecisions.push_back(ideologicalDecisions);
	});
	parseFile("ideologicalDecisions.txt");

	clearRegisteredKeywords();

	registerKeyword(std::regex("[A-Za-z\\_]+"), [this](const std::string& categoryName, std::istream& theStream)
	{
		const decisionsCategory category(categoryName, theStream);
		exiledGovernmentsDecisions.push_back(category);
	});
	parseFile(theConfiguration.getHoI4Path() + "/common/decisions/_exiled_governments_decisions.txt");

	clearRegisteredKeywords();
	registerKeyword(std::regex("[A-Za-z\\_]+"), [this](const std::string& categoryName, std::istream& theStream)
	{
		const decisionsCategory category(categoryName, theStream);
		foreignInfluenceDecisions.push_back(category);
	});
	parseFile(theConfiguration.getHoI4Path() + "/common/decisions/foreign_influence.txt");

	clearRegisteredKeywords();
	registerKeyword(std::regex("[A-Za-z\\_]+"), [this](const std::string& categoryName, std::istream& theStream)
	{
		const decisionsCategory category(categoryName, theStream);

		auto categoryMerged = false;
		for (auto& oldCategory: foreignInfluenceDecisions)
		{
			if (oldCategory.getName() == category.getName())
			{
				for (auto decision: category.getDecisions())
				{
					oldCategory.addDecision(decision);
				}
				categoryMerged = true;
			}
		}

		if (!categoryMerged)
		{
			foreignInfluenceDecisions.push_back(category);
		}
	});
	parseFile("DataFiles/foreignInfluenceDecisions.txt");

	clearRegisteredKeywords();
	registerKeyword(std::regex("[A-Za-z\\_]+"), [this](const std::string& categoryName, std::istream& theStream)
	{
		const decisionsCategory category(categoryName, theStream);
		mtgNavalTreatyDecisions.push_back(category);
	});
	parseFile(theConfiguration.getHoI4Path() + "/common/decisions/MTG_naval_treaty.txt");

	clearRegisteredKeywords();
	registerKeyword(std::regex("[A-Za-z\\_]+"), [this](const std::string& categoryName, std::istream& theStream)
	{
		const decisionsCategory category(categoryName, theStream);
		genericDecisions.push_back(category);
	});
	parseFile(theConfiguration.getHoI4Path() + "/common/decisions/_generic_decisions.txt");
}


void HoI4::decisions::updateDecisions(
	const std::set<std::string>& majorIdeologies,
	const std::map<int, int>& provinceToStateIdMap,
	const Events& theEvents
)
{
	stabilityDecisions.updateDecisions(majorIdeologies);
	updatePoliticalDecisions(majorIdeologies, theEvents);
	updateExiledGovernmentDecisions(majorIdeologies);
	updateForeignInfluenceDecisions(majorIdeologies);
	updateMtgNavalTreatyDecisions(majorIdeologies);
	updateGenericDecisions(provinceToStateIdMap, majorIdeologies);

	decisionsCategories = std::make_unique<DecisionsCategories>(majorIdeologies);
}


void HoI4::decisions::updatePoliticalDecisions(const std::set<std::string>& majorIdeologies, const Events& theEvents)
{
	for (auto ideologicalDecisions: allIdeologicalDecisions)
	{
		if (ideologicalDecisions.requiredIdeologiesExist(majorIdeologies))
		{
			for (const auto& category: ideologicalDecisions.getCategories())
			{
				auto existingCategory = std::find(politicalDecisions.begin(), politicalDecisions.end(), category);
				if (existingCategory == politicalDecisions.end())
				{
					politicalDecisions.push_back(category);
				}
				else
				{
					auto theDecisions = category.getDecisions();
					for (auto& theDecision: theDecisions)
					{
						existingCategory->addDecision(theDecision);
					}
				}
			}
		}
	}

	for (auto& decisionsByIdeology: politicalDecisions)
	{
		decisionsByIdeology.updatePoliticalDecisions(majorIdeologies, theEvents);
	}
}


bool exiledGovernmentDecisionToUpdate(const std::string& decisionName);


void HoI4::decisions::updateExiledGovernmentDecisions(const std::set<std::string>& majorIdeologies)
{
	for (auto category: exiledGovernmentsDecisions)
	{
		auto updated = false;
		for (auto decision: category.getDecisions())
		{
			if (exiledGovernmentDecisionToUpdate(decision.getName()))
			{
				std::stringstream available;
				available << "{\n";
				available << "\t\t\tFROM = {\n";
				available << "\t\t\t\thas_legitimacy > 50\n";
				available << "\t\t\t\tOR = {\n";
				for (const auto& ideology: majorIdeologies)
				{
					if ((ideology == "democratic") || (ideology == "neutrality"))
					{
						continue;
					}
					available << "\t\t\t\t\t" << ideology << " > 0.1\n";
				}
				available << "\t\t\t\t}\n";
				available << "\t\t\t}\n";
				available << "\t\t}";
				decision.setAvailable(available.str());

				std::stringstream visibleAndTT;
				visibleAndTT << "{\n";
				visibleAndTT << "\t\t\tFROM = {\n";
				visibleAndTT << "\t\t\t\tis_exiled_in = ROOT\n";
				visibleAndTT << "\t\t\t\thas_legitimacy > 40\n";
				visibleAndTT << "\t\t\t\tOR = {\n";
				for (const auto& ideology: majorIdeologies)
				{
					if ((ideology == "democratic") || (ideology == "neutrality"))
					{
						continue;
					}
					visibleAndTT << "\t\t\t\t\t" << ideology << " > 0.05\n";
				}
				visibleAndTT << "\t\t\t\t}\n";
				visibleAndTT << "\t\t\t}\n";
				visibleAndTT << "\t\t}";
				decision.setVisible(visibleAndTT.str());
				decision.setTargetTrigger(visibleAndTT.str());

				std::stringstream targetedModifier;
				targetedModifier << "{\n";
				targetedModifier << "\t\t\ttag = FROM\n";
				targetedModifier << "\t\t\ttargeted_legitimacy_daily = -1\n";
				if (majorIdeologies.count("democratic") > 0)
				{
					targetedModifier << "\t\t\tdemocratic_drift = 0.05\n";
				}
				else
				{
					targetedModifier << "\t\t\tneutrality_drift = 0.05\n";
				}
				targetedModifier << "\t\t}";
				decision.setTargetedModifier(targetedModifier.str());

				category.replaceDecision(decision);
				updated = true;
				break;
			}
		}
		if (updated)
		{
			std::replace(
				exiledGovernmentsDecisions.begin(),
				exiledGovernmentsDecisions.end(),
				category,
				category
			);
		}
	}
}


bool exiledGovernmentDecisionToUpdate(const std::string& decisionName)
{
	return (decisionName == "purge_infiltrators");
}


std::regex createIdeologyRegex(const std::set<std::string>& majorIdeologies);


void HoI4::decisions::updateForeignInfluenceDecisions(const std::set<std::string>& majorIdeologies)
{
	const auto ideologyRegex = createIdeologyRegex(majorIdeologies);
	for (auto& category: foreignInfluenceDecisions)
	{
		std::smatch ideologyMatch;
		auto decisions = category.getDecisions();
		decisions.erase(
			std::remove_if(
				decisions.begin(),
				decisions.end(),
				[&ideologyMatch, &ideologyRegex](auto& decision)
				{
					auto visible = decision.getVisible();
					return !std::regex_search(visible, ideologyMatch, ideologyRegex);
				}
			),
			decisions.end());
		category.replaceDecisions(decisions);

		for (auto decision: category.getDecisions())
		{
			auto visible = decision.getVisible();
			std::regex_search(visible, ideologyMatch, ideologyRegex);

			std::string newVisible;
			std::smatch typeMatch;
			if (std::regex_search(visible, typeMatch, std::regex("99")))
			{
				newVisible += "= {\n";
				newVisible += "\t\t\thas_government = " + ideologyMatch.str() + "\n";
				newVisible += "\t\t\tFROM = {\n";
				newVisible += "\t\t\t\tis_puppet_of = ROOT\n";
				newVisible += "\t\t\t\t" + ideologyMatch.str() + " < 0.99\n";
				newVisible += "\t\t\t}\n";
				newVisible += "\t\t}";
			}
			else
			{
				newVisible += "= {\n";
				newVisible += "\t\t\thas_government = " + ideologyMatch.str() + "\n";
				newVisible += "\t\t\tFROM = {\n";
				newVisible += "\t\t\t\tis_puppet_of = ROOT\n";
				newVisible += "\t\t\t\tNOT = { has_government = " + ideologyMatch.str() + " }\n";
				newVisible += "\t\t\t}\n";
				newVisible += "\t\t}";
			}

			decision.setVisible(newVisible);
			category.replaceDecision(decision);
		}
	}
}


std::regex createIdeologyRegex(const std::set<std::string>& majorIdeologies)
{
	std::string regexString{ "(" };
	for (const auto& ideology: majorIdeologies)
	{
		regexString += ideology + "|";
	}
	regexString.pop_back();
	regexString += ")";
	return std::regex{ regexString };
}


void HoI4::decisions::updateMtgNavalTreatyDecisions(const std::set<std::string>& majorIdeologies)
{
	for (auto& decisionsCategory : mtgNavalTreatyDecisions)
	{
		for (auto decision: decisionsCategory.getDecisions())
		{
			if (
					(decision.getName() == "MTG_abandon_treaty_democratic") &&
					(majorIdeologies.count("democratic") == 0)
				)
			{
				std::string newVisible = "= {\n";
				newVisible += "\t\t\thas_naval_treaty_trigger = yes\n";
				newVisible += "\t\t\tOR = { \n";
				newVisible += "\t\t\t\thas_government = neutrality\n";
				newVisible += "\t\t\t}\n";
				newVisible += "\t\t}";
				decision.setVisible(newVisible);
				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_abandon_treaty_fascist")
			{
				std::string newAiWillDo = "= {\n\t\t\tfactor = 1\n\t\t}";
				decision.setAiWillDo(newAiWillDo);

				std::string newVisible = "= {\n";
				newVisible += "\t\t\thas_naval_treaty_trigger = yes\n";
				newVisible += "\t\t\tOR = { \n";
				for (const auto& ideology: majorIdeologies)
				{
					if ((ideology == "democratic") || (ideology == "neutrality"))
					{
						continue;
					}
					newVisible += "\t\t\t\thas_government = " + ideology + "\n";
				}
				newVisible += "\t\t\t}\n";
				newVisible += "\t\t}";
				decision.setVisible(newVisible);

				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_cheat_on_treaty")
			{
				std::string newAiWillDo = "= {\n\t\t\tfactor = 0\n\t\t}";
				decision.setAiWillDo(newAiWillDo);

				std::string newVisible = "= {\n";
				newVisible += "\t\t\tOR = {\n";
				newVisible += "\t\t\t\thas_idea = MTG_naval_treaty_adherent\n";
				newVisible += "\t\t\t\thas_idea = MTG_naval_treaty_adherent_reduced\n";
				newVisible += "\t\t\t}\n";
				newVisible += "\t\t\tOR = {\n";
				for (const auto& ideology : majorIdeologies)
				{
					if ((ideology == "democratic") || (ideology == "neutrality"))
					{
						continue;
					}
					newVisible += "\t\t\t\thas_government = " + ideology + "\n";
				}
				newVisible += "\t\t\t}\n";
				newVisible += "\t\t}";
				decision.setVisible(newVisible);

				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_invite_FROM_to_treaty")
			{
				std::string newAiWillDo = "= {\n";
				newAiWillDo += "\t\t\tfactor = 3\n";
				if (majorIdeologies.count("democratic") > 0)
				{
					newAiWillDo += "\t\t\tmodifier = {\n";
					newAiWillDo += "\t\t\t\thas_government = democratic\n";
					newAiWillDo += "\t\t\t\tadd = 10\n";
					newAiWillDo += "\t\t\t}\n";
				}
				newAiWillDo += "\t\t}";
				decision.setAiWillDo(newAiWillDo);

				std::string newTargetTrigger = "= {\n";
				newTargetTrigger += "\t\t\tFROM = { \n";
				newTargetTrigger += "\t\t\t\thas_war = no\n";
				newTargetTrigger += "\t\t\t\thas_naval_treaty_trigger = no\n";
				newTargetTrigger += "\t\t\t\tNOT = { has_country_flag = MTG_naval_treaty_abandoned }\n";
				newTargetTrigger += "\t\t\t\tNOT = { has_country_flag = MTG_refused_naval_treaty }\n";
				newTargetTrigger += "\t\t\t\thas_navy_size = {\n";
				newTargetTrigger += "\t\t\t\t\ttype = capital_ship\n";
				newTargetTrigger += "\t\t\t\t\tsize > 15\n";
				newTargetTrigger += "\t\t\t\t}\n";
				newTargetTrigger += "\t\t\t}\n";
				newTargetTrigger += "\t\t}";
				decision.setTargetTrigger(newTargetTrigger);

				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_send_treaty_warning_to_FROM_previous_signatory")
			{
				std::string newAiWillDo = "= {\n\t\t\tfactor = 10\n\t\t}";
				decision.setAiWillDo(newAiWillDo);

				std::string newTargetTrigger = "= {\n";
				newTargetTrigger += "\t\t\tFROM = { \n";
				newTargetTrigger += "\t\t\t\thas_war = no\n";
				newTargetTrigger += "\t\t\t\thas_country_flag = MTG_naval_treaty_abandoned\n";
				newTargetTrigger += "\t\t\t\thas_navy_size = {\n";
				newTargetTrigger += "\t\t\t\t\ttype = capital_ship\n";
				newTargetTrigger += "\t\t\t\t\tsize > 20\n";
				newTargetTrigger += "\t\t\t\t}\n";
				newTargetTrigger += "\t\t\t}\n";
				newTargetTrigger += "\t\t}";
				decision.setTargetTrigger(newTargetTrigger);

				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_send_treaty_warning_to_FROM")
			{
				std::string newAiWillDo = "= {\n\t\t\tfactor = 10\n\t\t}";
				decision.setAiWillDo(newAiWillDo);

				std::string newTargetTrigger = "= {\n";
				newTargetTrigger += "\t\t\tFROM = {\n";
				newTargetTrigger += "\t\t\t\tOR = {\n";
				newTargetTrigger += "\t\t\t\t\tAND = {\n";
				newTargetTrigger += "\t\t\t\t\t\thas_war = no\n";
				newTargetTrigger += "\t\t\t\t\t\tnot = { has_country_flag = MTG_naval_treaty_abandoned }\n";
				newTargetTrigger += "\t\t\t\t\t\tNOT = { has_country_flag = MTG_refused_naval_treaty }\n";
				newTargetTrigger += "\t\t\t\t\t\thas_naval_treaty_trigger = no\n";
				newTargetTrigger += "\t\t\t\t\t\thas_navy_size = { \n";
				newTargetTrigger += "\t\t\t\t\t\t\ttype = capital_ship\n";
				newTargetTrigger += "\t\t\t\t\t\t\tsize > 50\n";
				newTargetTrigger += "\t\t\t\t\t\t}\n";
				newTargetTrigger += "\t\t\t\t\t}\n";
				newTargetTrigger += "\t\t\t\t\tAND = {\n";
				newTargetTrigger += "\t\t\t\t\t\thas_naval_treaty_trigger = yes\n";
				newTargetTrigger += "\t\t\t\t\t\thas_navy_size = {\n";
				newTargetTrigger += "\t\t\t\t\t\t\ttype = capital_ship\n";
				newTargetTrigger += "\t\t\t\t\t\t\tsize > 50\n";
				newTargetTrigger += "\t\t\t\t\t\t}\n";
				newTargetTrigger += "\t\t\t\t\t}\n";
				newTargetTrigger += "\t\t\t\t}\n";
				newTargetTrigger += "\t\t\t}\n";
				newTargetTrigger += "\t\t}";
				decision.setTargetTrigger(newTargetTrigger);

				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_treaty_reduction_mission")
			{
				std::string newAvailable = "= {\n";
				newAvailable += "\t\t\thas_navy_size = {\n";
				newAvailable += "\t\t\t\ttype = capital_ship\n";
				newAvailable += "\t\t\t\tsize < 20\n";
				newAvailable += "\t\t\t}\n";
				newAvailable += "\t\t}";
				decision.setAvailable(newAvailable);

				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_treaty_reduction_signatory_mission")
			{
				std::string newAvailable = "= {\n";
				newAvailable += "\t\t\thas_navy_size = {\n";
				newAvailable += "\t\t\t\ttype = capital_ship\n";
				newAvailable += "\t\t\t\tsize < 50\n";
				newAvailable += "\t\t\t}\n";
				newAvailable += "\t\t}";
				decision.setAvailable(newAvailable);

				decisionsCategory.replaceDecision(decision);
			}
		}
	}
}


void HoI4::decisions::updateGenericDecisions(
	const std::map<int, int>& provinceToStateIdMap,
	const std::set<std::string>& majorIdeologies
)
{
	for (auto& category : genericDecisions)
	{
		auto decisions = category.getDecisions();
		decisions.erase(
			std::remove_if(
				decisions.begin(),
				decisions.end(),
				[](auto& decision)
				{
					return decision.getName() == "dismantle_maginot";
				}
			),
			decisions.end());
		category.replaceDecisions(decisions);

		for (auto& decision : category.getDecisions())
		{
			if (decision.getName() == "blow_suez_canal")
			{
				std::set<int> relevantSelfProvinces{
					12049, // north-west suez canal
					4073, // south-west suez canal
					1155, // north-east suez canal
					9947 // south-east suez canal
				};

				std::set<int> relevantSelfStates;
				for (const auto& province : relevantSelfProvinces)
				{
					if (auto mapping = provinceToStateIdMap.find(province); mapping != provinceToStateIdMap.end())
					{
						relevantSelfStates.insert(mapping->second);
					}
				}

				std::set<int> relevantOtherProvinces{
					7079, 5078, 9989, 12033, 11967, 12091, 10061, 7148, 11910, // Marsa Matruh (452)
					1071, 4145, 4076, 7164, 7091, 10073, 11964, // Alexandria (447)
					992, 7117, 3996, 4055, 1068, 10031, 10005, 7011, 12004, 4143, 7188, // Cairo (446)
					7144, 7030, 11974, 10028, 12044, 1151, 10097, 7073, 12071, 1028, 1064, 11999, 1206, 12771, 10844, // Aswan (456)
					10126, 1080, 9957, 12002, 12889, 4068, 7156, 5069, 4910, // Eastern Desert (457)
					11979, 4161, 11922, 10002, 1112, 12073, 10099, // Sinai (453)
					1065, 1201, 4206, 4088, 11970, 7107, 1086, 7176, 1015, // Palestine (454)
					7170, 7001, 1544, 4440, 7151, 4574, 10089, 4017, 4591, 4562, 4115, 11976, 4603 // Jordan (455)
				};

				std::set<int> relevantOtherStates;
				for (const auto& province: relevantOtherProvinces)
				{
					if (
						auto mapping = provinceToStateIdMap.find(province);
						mapping != provinceToStateIdMap.end() && (relevantSelfStates.count(mapping->second) == 0)
						)
					{
						relevantOtherStates.insert(mapping->second);
					}
				}

				std::set<int> relevantNileProvinces{
					7144, 7030, 11974, 10028, 12044, 1151, 10097, 7073, 12071, 1028, 1064, 11999, 1206, 12771, 10844, // Aswan (456)
					10126, 1080, 9957, 12002, 12889, 4068, 7156, 5069, 4910, // Eastern Desert (457)
				};

				std::set<int> relevantNileStates;
				for (const auto& province: relevantNileProvinces)
				{
					if (auto mapping = provinceToStateIdMap.find(province); mapping != provinceToStateIdMap.end())
					{
						relevantNileStates.insert(mapping->second);
					}
				}

				std::set<int> relevantLandRouteProvinces{ 1977, 12725, 2003	}; // Khartoum

				std::set<int> relevantLandRouteStates;
				for (const auto& province: relevantLandRouteProvinces)
				{
					if (auto mapping = provinceToStateIdMap.find(province); mapping != provinceToStateIdMap.end())
					{
						relevantLandRouteStates.insert(mapping->second);
					}
				}

				std::set<int> relevantSupplyProvinces{
					5047, 5091, 12766, 8043, // Eritria
					4985, 8124, 10777, 10833, 12759, 10921, 1966, 10891, 10818, 12840, 5065, 12991, 10928, 8164, 12941 // Somaliland
				};

				std::set<int> relevantSupplyStates;
				for (const auto& province: relevantSupplyProvinces)
				{
					if (auto mapping = provinceToStateIdMap.find(province); mapping != provinceToStateIdMap.end())
					{
						relevantSupplyStates.insert(mapping->second);
					}
				}

				std::optional<int> gibraltar;
				if (auto mapping = provinceToStateIdMap.find(4135); mapping != provinceToStateIdMap.end())
				{
					gibraltar = mapping->second;
				}

				std::string available;
				available += "= {\n";
				for (const auto state: relevantSelfStates)
				{
					available += "\t\t\tcontrols_state = " + std::to_string(state) + "\n";
				}
				available += "\t\t\tOR = { \n";
				available += "\t\t\t\tNOT = { \n";
				for (const auto state : relevantSelfStates)
				{
					available += "\t\t\t\t\towns_state = " + std::to_string(state) + "\n";
				}
				available += "\t\t\t\t}\n";
				available += "\t\t\t\tany_enemy_country = { \n";
				available += "\t\t\t\t\tOR = { \n";
				for (const auto state: relevantOtherStates)
				{
					available += "\t\t\t\t\t\tcontrols_state = " + std::to_string(state) + "\n";
				}
				available += "\t\t\t\t\t}\n";
				available += "\t\t\t\t}\n";
				available += "\t\t\t}\n";
				available += "\t\t}";
				decision.setAvailable(available);

				std::string completeEffect;
				completeEffect += "= { \n";
				completeEffect += "\t\t\thidden_effect = { \n";
				completeEffect += "\t\t\t\tif = { \n";
				completeEffect += "\t\t\t\t\tlimit = { \n";
				completeEffect += "\t\t\t\t\t\tNOT = { \n";
				for (const auto state: relevantSelfStates)
				{
					completeEffect += "\t\t\t\t\t\t\towns_state = " + std::to_string(state) + "\n";
				}
				completeEffect += "\t\t\t\t\t\t}\n";
				completeEffect += "\t\t\t\t\t}\n";
				completeEffect += "\t\t\t\t\trandom_country = { \n";
				completeEffect += "\t\t\t\t\t\tlimit = { \n";
				for (const auto state: relevantSelfStates)
				{
					completeEffect += "\t\t\t\t\t\t\towns_state = " + std::to_string(state) + "\n";
				}
				completeEffect += "\t\t\t\t\t\t}\n";
				completeEffect += "\t\t\t\t\t\tcountry_event = { id = generic.12 days = 1 }\n";
				completeEffect += "\t\t\t\t\t}\n";
				completeEffect += "\t\t\t\t}\n";
				completeEffect += "\t\t\t}\n";
				completeEffect += "\t\t}";
				decision.setCompleteEffect(completeEffect);

				std::string removeEffect;
				removeEffect += "= { \n";
				removeEffect += "\t\t\tif = { \n";
				removeEffect += "\t\t\t\tlimit = { \n";
				removeEffect += "\t\t\t\t\tOR = { \n";
				for (const auto state: relevantSelfStates)
				{
					removeEffect += "\t\t\t\t\t\thas_full_control_of_state = " + std::to_string(state) + "\n";
				}
				removeEffect += "\t\t\t\t\t}\n";
				removeEffect += "\t\t\t\t}\n";
				removeEffect += "\t\t\t\tset_country_flag = blew_up_suez\n";
				removeEffect += "\t\t\t\tset_global_flag = SUEZ_CANAL_BLOCKED\n";
				removeEffect += "\t\t\t\tcountry_event = { id = wtt_news.40 hours = 6}\n";
				removeEffect += "\t\t\t}\n";
				removeEffect += "\t\t}";
				decision.setRemoveEffect(removeEffect);

				std::string aiWillDo;
				aiWillDo += "= { \n";
				aiWillDo += "\t\t\tfactor = 1\n";
				aiWillDo += "\t\t\tmodifier = { \n";
				aiWillDo += "\t\t\t\tfactor = 0\n";
				aiWillDo += "\t\t\t\tNOT = { \n";
				aiWillDo += "\t\t\t\t\tany_enemy_country = { \n";
				aiWillDo += "\t\t\t\t\t\tOR = { \n";
				for (const auto state: relevantOtherStates)
				{
					aiWillDo += "\t\t\t\t\t\t\tcontrols_state = " + std::to_string(state) + "\n";
				}
				aiWillDo += "\t\t\t\t\t\t\tOR = { \n";
				for (const auto state: relevantOtherStates)
				{
					aiWillDo += "\t\t\t\t\t\t\t\tdivisions_in_state = { state = " + std::to_string(state) + " size > 2 }\n";
				}
				aiWillDo += "\t\t\t\t\t\t\t}\n";
				aiWillDo += "\t\t\t\t\t\t}\n";
				aiWillDo += "\t\t\t\t\t}\n";
				aiWillDo += "\t\t\t\t}\n";
				aiWillDo += "\t\t\t}\n";
				aiWillDo += "\t\t\tmodifier = { \n";
				aiWillDo += "\t\t\t\tfactor = 0 # Don't blow the canal when you've got troops needing supplies in the Horn of Africa,and no land route has been established there\n";
				aiWillDo += "\t\t\t\tany_allied_country = { \n";
				aiWillDo += "\t\t\t\t\tNOT = { \n";
				aiWillDo += "\t\t\t\t\t\tOR = { \n";
				for (const auto state: relevantNileStates)
				{
					aiWillDo += "\t\t\t\t\t\t\thas_full_control_of_state = " + std::to_string(state) + "\n";
				}
				aiWillDo += "\t\t\t\t\t\t}\n";
				aiWillDo += "\t\t\t\t\t}\n";
				for (const auto& state: relevantLandRouteStates)
				{
					aiWillDo += "\t\t\t\t\tNOT = { has_full_control_of_state = " + std::to_string(state) + " }\n";
				}
				aiWillDo += "\t\t\t\t\tOR = { \n";
				for (const auto& state: relevantSupplyStates)
				{
					aiWillDo += "\t\t\t\t\t\tdivisions_in_state = { state = " + std::to_string(state) + " size > 0 }\n";
				}
				aiWillDo += "\t\t\t\t\t}\n";
				aiWillDo += "\t\t\t\t}\n";
				aiWillDo += "\t\t\t}\n";
				if (gibraltar)
				{
					aiWillDo += "\t\t\tmodifier = { \n";
					aiWillDo += "\t\t\t\tfactor = 200 # Try to cut the enemy off from the mediterranean if you also occupy Gibraltar\n";
					aiWillDo += "\t\t\t\tOR = { \n";
					aiWillDo += "\t\t\t\t\thas_full_control_of_state = " + std::to_string(*gibraltar) + "\n";
					aiWillDo += "\t\t\t\t\tany_allied_country = { \n";
					aiWillDo += "\t\t\t\t\t\thas_full_control_of_state = " + std::to_string(*gibraltar) + "\n";
					aiWillDo += "\t\t\t\t\t}\n";
					aiWillDo += "\t\t\t\t}\n";
					aiWillDo += "\t\t\t\thas_war = yes\n";
					aiWillDo += "\t\t\t}\n";
				}
				aiWillDo += "\t\t}";
				decision.setAiWillDo(aiWillDo);

				category.replaceDecision(decision);
			}
		}
	}
}