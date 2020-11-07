#include "GenericDecisions.h"



HoI4::decision&& updateBlowSuez(HoI4::decision&& blowSuezDecision, const std::map<int, int>& provinceToStateIdMap);
HoI4::decision&& updateBlowPanama(HoI4::decision&& blowPanamaDecision, const std::map<int, int>& provinceToStateIdMap);
HoI4::decision&& updateRebuildSuez(HoI4::decision&& rebuildSuezDecision,
	 const std::map<int, int>& provinceToStateIdMap);
HoI4::decision&& updateRebuildPanama(HoI4::decision&& rebuildPanamaDecision,
	 const std::map<int, int>& provinceToStateIdMap);
HoI4::decision&& updateWomenInTheWorkforce(HoI4::decision&& womenInTheWorkforceDecision,
	 const std::set<std::string>& majorIdeologies);
HoI4::decision&& updateWarBonds(HoI4::decision&& warBondsDecision, const std::set<std::string>& majorIdeologies);
HoI4::decision&& updateImprovedWorkerConditions(HoI4::decision&& improvedWorkerConditionsDecision);
HoI4::decision&& updatePromisesOfPeace(HoI4::decision&& promisesOfPeaceDecision);
HoI4::decision&& updateWarPropaganda(HoI4::decision&& warPropagandaDecision);
HoI4::decision&& updateWarPropagandaAgainstWarmonger(HoI4::decision&& warPropagandaDecision);
HoI4::decision&& updateObjectToAttaches(HoI4::decision&& objectToAttachesDecision);



void HoI4::GenericDecisions::updateDecisions(const std::map<int, int>& provinceToStateIdMap,
	 const std::set<std::string>& majorIdeologies)
{
	for (auto& category: decisions)
	{
		if (category.getName() == "economy_decisions")
		{
			auto decisions = category.getDecisions();
			decisions.erase(std::remove_if(decisions.begin(),
									  decisions.end(),
									  [](auto& decision) {
										  return decision.getName() == "dismantle_maginot";
									  }),
				 decisions.end());
			category.replaceDecisions(decisions);
		}

		for (auto& decision: category.getDecisions())
		{
			if (decision.getName() == "blow_suez_canal")
			{
				category.replaceDecision(updateBlowSuez(std::move(decision), provinceToStateIdMap));
			}
			else if (decision.getName() == "blow_panama_canal")
			{
				category.replaceDecision(updateBlowPanama(std::move(decision), provinceToStateIdMap));
			}
			else if (decision.getName() == "rebuild_suez_canal")
			{
				category.replaceDecision(updateRebuildSuez(std::move(decision), provinceToStateIdMap));
			}
			else if (decision.getName() == "rebuild_panama_canal")
			{
				category.replaceDecision(updateRebuildPanama(std::move(decision), provinceToStateIdMap));
			}
			else if (decision.getName() == "women_in_the_workforce")
			{
				category.replaceDecision(updateWomenInTheWorkforce(std::move(decision), majorIdeologies));
			}
			else if (decision.getName() == "war_bonds")
			{
				category.replaceDecision(updateWarBonds(std::move(decision), majorIdeologies));
			}
			else if (decision.getName() == "improved_worker_conditions")
			{
				category.replaceDecision(updateImprovedWorkerConditions(std::move(decision)));
			}
			else if (decision.getName() == "promises_of_peace")
			{
				category.replaceDecision(updatePromisesOfPeace(std::move(decision)));
			}
			else if (decision.getName() == "war_propaganda")
			{
				category.replaceDecision(updateWarPropaganda(std::move(decision)));
			}
			else if (decision.getName() == "war_propaganda_against_warmonger")
			{
				category.replaceDecision(updateWarPropagandaAgainstWarmonger(std::move(decision)));
			}
			else if (decision.getName() == "object_to_attaches")
			{
				category.replaceDecision(updateObjectToAttaches(std::move(decision)));
			}
		}
	}

	decisions.erase(std::remove_if(decisions.begin(),
							  decisions.end(),
							  [](auto& decisionCategory) {
								  return decisionCategory.getName() == "foreign_support";
							  }),
		 decisions.end());
}


std::set<int> getRelevantStatesFromProvinces(const std::set<int>& provinces,
	 const std::set<int>& statesToExclude,
	 const std::map<int, int>& provinceToStateIdMap);


HoI4::decision&& updateBlowSuez(HoI4::decision&& blowSuezDecision, const std::map<int, int>& provinceToStateIdMap)
{
	auto relevantCanalStates = getRelevantStatesFromProvinces(
		 {
			  12049, // north-west suez canal
			  4073,	// south-west suez canal
			  1155,	// north-east suez canal
			  9947	// south-east suez canal
		 },
		 {},
		 provinceToStateIdMap);

	auto relevantOtherStates = getRelevantStatesFromProvinces(
		 {
			  7079,
			  5078,
			  9989,
			  12033,
			  11967,
			  12091,
			  10061,
			  7148,
			  11910, // Marsa Matruh (452)
			  1071,
			  4145,
			  4076,
			  7164,
			  7091,
			  10073,
			  11964, // Alexandria (447)
			  992,
			  7117,
			  3996,
			  4055,
			  1068,
			  10031,
			  10005,
			  7011,
			  12004,
			  4143,
			  7188, // Cairo (446)
			  7144,
			  7030,
			  11974,
			  10028,
			  12044,
			  1151,
			  10097,
			  7073,
			  12071,
			  1028,
			  1064,
			  11999,
			  1206,
			  12771,
			  10844, // Aswan (456)
			  10126,
			  1080,
			  9957,
			  12002,
			  12889,
			  4068,
			  7156,
			  5069,
			  4910, // Eastern Desert (457)
			  11979,
			  4161,
			  11922,
			  10002,
			  1112,
			  12073,
			  10099, // Sinai (453)
			  1065,
			  1201,
			  4206,
			  4088,
			  11970,
			  7107,
			  1086,
			  7176,
			  1015, // Palestine (454)
			  7170,
			  7001,
			  1544,
			  4440,
			  7151,
			  4574,
			  10089,
			  4017,
			  4591,
			  4562,
			  4115,
			  11976,
			  4603 // Jordan (455)
		 },
		 relevantCanalStates,
		 provinceToStateIdMap);

	auto relevantNileStates = getRelevantStatesFromProvinces(
		 {
			  7144,
			  7030,
			  11974,
			  10028,
			  12044,
			  1151,
			  10097,
			  7073,
			  12071,
			  1028,
			  1064,
			  11999,
			  1206,
			  12771,
			  10844, // Aswan (456)
			  10126,
			  1080,
			  9957,
			  12002,
			  12889,
			  4068,
			  7156,
			  5069,
			  4910, // Eastern Desert (457)
		 },
		 {},
		 provinceToStateIdMap);

	auto relevantLandRouteStates = getRelevantStatesFromProvinces({1977, 12725, 2003}, // Khartoum
		 {},
		 provinceToStateIdMap);

	auto relevantSupplyStates = getRelevantStatesFromProvinces(
		 {
			  5047,
			  5091,
			  12766,
			  8043, // Eritria
			  4985,
			  8124,
			  10777,
			  10833,
			  12759,
			  10921,
			  1966,
			  10891,
			  10818,
			  12840,
			  5065,
			  12991,
			  10928,
			  8164,
			  12941 // Somaliland
		 },
		 {},
		 provinceToStateIdMap);

	std::optional<int> gibraltar;
	if (auto mapping = provinceToStateIdMap.find(4135); mapping != provinceToStateIdMap.end())
	{
		gibraltar = mapping->second;
	}

	std::string available;
	available += "= {\n";
	for (const auto state: relevantCanalStates)
	{
		available += "\t\t\tcontrols_state = " + std::to_string(state) + "\n";
	}
	available += "\t\t\tOR = { \n";
	available += "\t\t\t\tNOT = { \n";
	for (const auto state: relevantCanalStates)
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
	blowSuezDecision.setAvailable(available);

	std::string completeEffect;
	completeEffect += "= { \n";
	completeEffect += "\t\t\thidden_effect = { \n";
	completeEffect += "\t\t\t\tif = { \n";
	completeEffect += "\t\t\t\t\tlimit = { \n";
	completeEffect += "\t\t\t\t\t\tNOT = { \n";
	for (const auto state: relevantCanalStates)
	{
		completeEffect += "\t\t\t\t\t\t\towns_state = " + std::to_string(state) + "\n";
	}
	completeEffect += "\t\t\t\t\t\t}\n";
	completeEffect += "\t\t\t\t\t}\n";
	completeEffect += "\t\t\t\t\trandom_country = { \n";
	completeEffect += "\t\t\t\t\t\tlimit = { \n";
	for (const auto state: relevantCanalStates)
	{
		completeEffect += "\t\t\t\t\t\t\towns_state = " + std::to_string(state) + "\n";
	}
	completeEffect += "\t\t\t\t\t\t}\n";
	completeEffect += "\t\t\t\t\t\tcountry_event = { id = generic.12 days = 1 }\n";
	completeEffect += "\t\t\t\t\t}\n";
	completeEffect += "\t\t\t\t}\n";
	completeEffect += "\t\t\t}\n";
	completeEffect += "\t\t}";
	blowSuezDecision.setCompleteEffect(completeEffect);

	std::string removeEffect;
	removeEffect += "= { \n";
	removeEffect += "\t\t\tif = { \n";
	removeEffect += "\t\t\t\tlimit = { \n";
	removeEffect += "\t\t\t\t\tOR = { \n";
	for (const auto state: relevantCanalStates)
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
	blowSuezDecision.setRemoveEffect(removeEffect);

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
	aiWillDo +=
		 "\t\t\t\tfactor = 0 # Don't blow the canal when you've got troops needing supplies in the Horn of Africa,and no "
		 "land route has been established there\n";
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
		aiWillDo +=
			 "\t\t\t\tfactor = 200 # Try to cut the enemy off from the mediterranean if you also occupy Gibraltar\n";
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
	blowSuezDecision.setAiWillDo(aiWillDo);

	return std::move(blowSuezDecision);
}


HoI4::decision&& updateBlowPanama(HoI4::decision&& blowPanamaDecision, const std::map<int, int>& provinceToStateIdMap)
{
	auto canalState = getRelevantStatesFromProvinces(
		 {
			  7617 // Panama province
		 },
		 {},
		 provinceToStateIdMap);

	auto peninsulaState = getRelevantStatesFromProvinces(
		 {
			  10482,
			  7630,
			  7617,
			  4624,
			  1633,
			  4611 // Panama state
		 },
		 {},
		 provinceToStateIdMap);

	std::string available;
	available += "= {\n";
	for (const auto state: canalState)
	{
		available += "\t\t\thas_full_control_of_state = " + std::to_string(state) + "\n";
	}
	available += "\t\t}";
	blowPanamaDecision.setAvailable(available);

	std::string completeEffect;
	completeEffect += "= {\n";
	completeEffect += "\t\t\thidden_effect = {\n";
	completeEffect += "\t\t\t\tif = {\n";
	completeEffect += "\t\t\t\t\tlimit = {\n";
	completeEffect += "\t\t\t\t\t\tNOT = {\n";
	for (const auto state: canalState)
	{
		completeEffect += "\t\t\t\t\t\t\towns_state = " + std::to_string(state) + "\n";
	}
	completeEffect += "\t\t\t\t\t\t}\n";
	completeEffect += "\t\t\t\t\t}\n";
	completeEffect += "\t\t\t\t\trandom_country = {\n";
	completeEffect += "\t\t\t\t\t\tlimit = {\n";
	for (const auto state: canalState)
	{
		completeEffect += "\t\t\t\t\t\t\towns_state = " + std::to_string(state) + "\n";
	}
	completeEffect += "\t\t\t\t\t\t}\n";
	completeEffect += "\t\t\t\t\t\tcountry_event = { id = generic.13 days = 1 }\n";
	completeEffect += "\t\t\t\t\t}\n";
	completeEffect += "\t\t\t\t}\n";
	completeEffect += "\t\t\t}\n";
	completeEffect += "\t\t}";
	blowPanamaDecision.setCompleteEffect(completeEffect);

	std::string removeEffect;
	removeEffect += "= {\n";
	removeEffect += "\t\t\tif = {\n";
	removeEffect += "\t\t\t\tlimit = {\n";
	removeEffect += "\t\t\t\t\tOR = {\n";
	for (const auto state: peninsulaState)
	{
		removeEffect += "\t\t\t\t\t\thas_full_control_of_state = " + std::to_string(state) + "\n";
	}
	removeEffect += "\t\t\t\t\t}\n";
	removeEffect += "\t\t\t\t}\n";
	removeEffect += "\t\t\t\tset_country_flag = blew_up_panama\n";
	removeEffect += "\t\t\t\tset_global_flag = PANAMA_CANAL_BLOCKED\n";
	removeEffect += "\t\t\t\tcountry_event = { id = wtt_news.41 hours = 6}\n";
	removeEffect += "\t\t\t}\n";
	removeEffect += "\t\t}";
	blowPanamaDecision.setRemoveEffect(removeEffect);

	std::string aiWillDo;
	aiWillDo += "= {\n";
	aiWillDo += "\t\t\tfactor = 1\n";
	aiWillDo += "\t\t\tmodifier = {\n";
	aiWillDo += "\t\t\t\tfactor = 0\n";
	aiWillDo += "\t\t\t\thas_navy_size = {\n";
	aiWillDo += "\t\t\t\t\tsize > 50\n";
	aiWillDo += "\t\t\t\t}\n";
	aiWillDo += "\t\t\t\tNOT = {\n";
	aiWillDo += "\t\t\t\t\tany_enemy_country = {\n";
	aiWillDo += "\t\t\t\t\t\thas_navy_size = {\n";
	aiWillDo += "\t\t\t\t\t\t\tsize > 50\n";
	aiWillDo += "\t\t\t\t\t\t}\n";
	aiWillDo += "\t\t\t\t\t}\n";
	aiWillDo += "\t\t\t\t}\n";
	aiWillDo += "\t\t\t}\n";
	aiWillDo += "\t\t}";
	blowPanamaDecision.setAiWillDo(aiWillDo);

	return std::move(blowPanamaDecision);
}


std::set<int> getRelevantStatesFromProvinces(const std::set<int>& provinces,
	 const std::set<int>& statesToExclude,
	 const std::map<int, int>& provinceToStateIdMap)
{
	std::set<int> relevantStates;
	for (const auto& province: provinces)
	{
		if (auto mapping = provinceToStateIdMap.find(province);
			 mapping != provinceToStateIdMap.end() && !statesToExclude.contains(mapping->second))
		{
			relevantStates.insert(mapping->second);
		}
	}

	return relevantStates;
}


HoI4::decision&& updateRebuildSuez(HoI4::decision&& rebuildSuezDecision, const std::map<int, int>& provinceToStateIdMap)
{
	auto relevantCanalStates = getRelevantStatesFromProvinces(
		 {
			  12049, // north-west suez canal
			  4073,	// south-west suez canal
			  1155,	// north-east suez canal
			  9947	// south-east suez canal
		 },
		 {},
		 provinceToStateIdMap);

	std::string available;
	available += "= {\n";
	for (const auto& state: relevantCanalStates)
	{
		available += "\t\t\thas_full_control_of_state = " + std::to_string(state) + "\n";
	}
	available += "\t\t\tnum_of_civilian_factories > 15\n";
	available += "\t\t}";
	rebuildSuezDecision.setAvailable(available);

	std::string removeEffect;
	removeEffect += "= {\n";
	removeEffect += "\t\t\tif = {\n";
	removeEffect += "\t\t\t\tlimit = {\n";
	for (const auto& state: relevantCanalStates)
	{
		removeEffect += "\t\t\t\thas_full_control_of_state = " + std::to_string(state) + "\n";
	}
	removeEffect += "\t\t\t\t}\n";
	removeEffect += "\t\t\t\tset_country_flag = rebuilt_suez\n";
	removeEffect += "\t\t\t\tclr_global_flag = SUEZ_CANAL_BLOCKED\n";
	removeEffect += "\t\t\t\tcountry_event = { id = wtt_news.42 hours = 6}\n";
	removeEffect += "\t\t\t}\n";
	removeEffect += "\t\t}";
	rebuildSuezDecision.setRemoveEffect(removeEffect);

	std::string aiWillDo;
	aiWillDo += "= {\n";
	aiWillDo += "\t\t\tfactor = 1\n";
	aiWillDo += "\t\t\tmodifier = {\n";
	aiWillDo += "\t\t\t\tfactor = 0 # Don't bother if your navy is weak\n";
	aiWillDo += "\t\t\t\thas_navy_size = { size < 100 }\n";
	aiWillDo += "\t\t\t}\n";
	aiWillDo += "\t\t\tmodifier = {\n";
	aiWillDo += "\t\t\t\tfactor = 10 # Prioritize if not at war\n";
	aiWillDo += "\t\t\t\thas_war = no\n";
	aiWillDo += "\t\t\t}\n";
	aiWillDo += "\t\t}";
	rebuildSuezDecision.setAiWillDo(aiWillDo);

	return std::move(rebuildSuezDecision);
}


HoI4::decision&& updateRebuildPanama(HoI4::decision&& rebuildPanamaDecision,
	 const std::map<int, int>& provinceToStateIdMap)
{
	auto canalState = getRelevantStatesFromProvinces(
		 {
			  7617 // Panama province
		 },
		 {},
		 provinceToStateIdMap);

	auto peninsulaState = getRelevantStatesFromProvinces(
		 {
			  10482,
			  7630,
			  7617,
			  4624,
			  1633,
			  4611 // Panama state
		 },
		 canalState,
		 provinceToStateIdMap);

	std::string available;
	available += "= {\n";
	for (const auto& state: canalState)
	{
		available += "\t\t\thas_full_control_of_state = " + std::to_string(state) + "\n";
	}
	available += "\t\t\tNOT = {\n";
	available += "\t\t\t\tany_enemy_country = {\n";
	for (const auto& state: peninsulaState)
	{
		available += "\t\t\t\t\tcontrols_state = " + std::to_string(state) + "\n";
	}
	available += "\t\t\t\t}\n";
	available += "\t\t\t}\n";
	available += "\t\t\tnum_of_civilian_factories > 25\n";
	available += "\t\t}";
	rebuildPanamaDecision.setAvailable(available);

	std::string removeEffect;
	removeEffect += "= {\n";
	removeEffect += "\t\t\tif = {\n";
	removeEffect += "\t\t\t\tlimit = {\n";
	for (const auto& state: canalState)
	{
		removeEffect += "\t\t\t\t\thas_full_control_of_state = " + std::to_string(state) + "\n";
	}
	removeEffect += "\t\t\t\t\tNOT = {\n";
	removeEffect += "\t\t\t\t\t\tany_enemy_country = {\n";
	for (const auto& state: peninsulaState)
	{
		removeEffect += "\t\t\t\t\t\t\tcontrols_state = " + std::to_string(state) + "\n";
	}
	removeEffect += "\t\t\t\t\t\t}\n";
	removeEffect += "\t\t\t\t\t}\n";
	removeEffect += "\t\t\t\t}\n";
	removeEffect += "\t\t\t\tset_country_flag = rebuilt_panama\n";
	removeEffect += "\t\t\t\tclr_global_flag = PANAMA_CANAL_BLOCKED\n";
	removeEffect += "\t\t\t\tcountry_event = { id = wtt_news.43 hours = 6 }\n";
	removeEffect += "\t\t\t}\n";
	removeEffect += "\t\t}";
	rebuildPanamaDecision.setRemoveEffect(removeEffect);

	std::string aiWillDo;
	aiWillDo += "= {\n";
	aiWillDo += "\t\t\tfactor = 1\n";
	aiWillDo += "\t\t\tmodifier = {\n";
	aiWillDo += "\t\t\t\tfactor = 0 # Don't bother if your navy is weak\n";
	aiWillDo += "\t\t\t\thas_navy_size = { size < 50 }\n";
	aiWillDo += "\t\t\t\thas_war = yes\n";
	aiWillDo += "\t\t\t}\n";
	aiWillDo += "\t\t\tmodifier = {\n";
	aiWillDo += "\t\t\t\tfactor = 10 # Prioritize if not at war\n";
	aiWillDo += "\t\t\t\thas_war = no\n";
	aiWillDo += "\t\t\t}\n";
	aiWillDo += "\t\t}";
	rebuildPanamaDecision.setAiWillDo(aiWillDo);

	return std::move(rebuildPanamaDecision);
}


HoI4::decision&& updateWomenInTheWorkforce(HoI4::decision&& womenInTheWorkforceDecision,
	 const std::set<std::string>& majorIdeologies)
{
	std::string available;
	available += "= {\n";
	available += "\t\t\thas_war = yes\n";
	available += "\t\t\thas_idea = tot_economic_mobilisation\n";
	available += "\t\t\tOR = {\n";
	for (const auto& ideology: majorIdeologies)
	{
		if (ideology == "neutrality")
		{
			continue;
		}

		available += "\t\t\t\tAND = {\n";
		available += "\t\t\t\t\thas_government = " + ideology + "\n";
		available += "\t\t\t\t\thas_war_support > 0.79\n";
		if (ideology == "fascism")
		{
			available += "\t\t\t\t\tsurrender_progress > 0\n";
		}
		available += "\t\t\t\t}\n";
	}
	available += "\t\t\t\tAND = {\n";
	available += "\t\t\t\t\thas_government = neutrality\n";
	available += "\t\t\t\t\thas_war_support > 0.84\n";
	available += "\t\t\t\t\thas_stability > 0.7\n";
	available += "\t\t\t\t}\n";
	available += "\t\t\t}\n";
	available += "\t\t}";
	womenInTheWorkforceDecision.setAvailable(available);

	womenInTheWorkforceDecision.setCompleteEffect("= {\n\t\t}");

	return std::move(womenInTheWorkforceDecision);
}


HoI4::decision&& updateWarBonds(HoI4::decision&& warBondsDecision, const std::set<std::string>& majorIdeologies)
{
	std::string available;
	available += "= {\n";
	available += "\t\t\thas_war = yes\n";
	available += "\t\t\tOR = {\n";
	for (const auto& ideology: majorIdeologies)
	{
		if (ideology == "neutrality")
		{
			continue;
		}

		available += "\t\t\t\tAND = {\n";
		available += "\t\t\t\t\thas_government = " + ideology + "\n";
		available += "\t\t\t\t\thas_war_support > 0.79\n";
		if (ideology == "fascism")
		{
			available += "\t\t\t\t\tsurrender_progress > 0\n";
		}
		available += "\t\t\t\t}\n";
	}
	available += "\t\t\t\tAND = {\n";
	available += "\t\t\t\t\thas_government = neutrality\n";
	available += "\t\t\t\t\thas_war_support > 0.84\n";
	available += "\t\t\t\t\thas_stability > 0.7\n";
	available += "\t\t\t\t}\n";
	available += "\t\t\t}\n";
	available += "\t\t}";
	warBondsDecision.setAvailable(available);

	std::string aiWillDo;
	aiWillDo += "= {\n";
	aiWillDo += "\t\t\tfactor = 1\n";
	aiWillDo += "\t\t\tmodifier = {\n";
	aiWillDo += "\t\t\t\thas_political_power < 100\n";
	aiWillDo += "\t\t\t\tfactor = 0 #use as pp dump\n";
	aiWillDo += "\t\t\t}\n";
	aiWillDo += "\t\t}";
	warBondsDecision.setAiWillDo(aiWillDo);

	warBondsDecision.setVisible(
		 "={\n"
		 "\t\t\thas_war = yes\n"
		 "\t\t}");

	return std::move(warBondsDecision);
}


HoI4::decision&& updateImprovedWorkerConditions(HoI4::decision&& improvedWorkerConditionsDecision)
{
	improvedWorkerConditionsDecision.setAvailable(
		 "= {\n"
		 "\t\t\thas_stability < 1.0\n"
		 "\t\t}");
	improvedWorkerConditionsDecision.setAiWillDo(
		 "= {\n"
		 "\t\t\tbase = 0\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tadd = 1\n"
		 "\t\t\t\thas_stability < 0.6\n"
		 "\t\t\t}\n"
		 "\t\t}");

	return std::move(improvedWorkerConditionsDecision);
}


HoI4::decision&& updatePromisesOfPeace(HoI4::decision&& promisesOfPeaceDecision)
{
	promisesOfPeaceDecision.setAvailable(
		 "= {\n"
		 "\t\t\thas_war = no\n"
		 "\t\t\thas_war_support > 0.2\n"
		 "\t\t\thas_stability < 1.0\n"
		 "\t\t}");
	promisesOfPeaceDecision.setAiWillDo(
		 "= {\n"
		 "\t\t\tbase = 0\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tadd = 1\n"
		 "\t\t\t\thas_stability < 0.4\n"
		 "\t\t\t}\n"
		 "\t\t}");

	return std::move(promisesOfPeaceDecision);
}


HoI4::decision&& updateWarPropaganda(HoI4::decision&& warPropagandaDecision)
{
	warPropagandaDecision.setAvailable(
		 "= {\n"
		 "\t\t\tNOT = { has_country_flag = war_propaganda_campaign_running }\n"
		 "\t\t\tthreat > 0.5\n"
		 "\t\t\thas_war_support < 0.5\n"
		 "\t\t\thas_offensive_war = no\n"
		 "\t\t}");

	return std::move(warPropagandaDecision);
}


HoI4::decision&& updateWarPropagandaAgainstWarmonger(HoI4::decision&& warPropagandaDecision)
{
	warPropagandaDecision.setAvailable(
		 "= {\n"
		 "\t\t\tNOT = { has_country_flag = war_propaganda_campaign_running }\n"
		 "\t\t\tFROM = {\n"
		 "\t\t\t\tOR = {\n"
		 "\t\t\t\t\tis_justifying_wargoal_against = ROOT\n"
		 "\t\t\t\t\tAND = {\n"
		 "\t\t\t\t\t\thas_war_with = ROOT\n"
		 "\t\t\t\t\t\tis_neighbor_of = ROOT\n"
		 "\t\t\t\t\t}\n"
		 "\t\t\t\t\thas_offensive_war = yes\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t}");

	return std::move(warPropagandaDecision);
}


HoI4::decision&& updateObjectToAttaches(HoI4::decision&& objectToAttachesDecision)
{
	objectToAttachesDecision.setVisible(
		 "= {\n"
		 "\t\t\tFROM = {\n"
		 "\t\t\t\tNOT = { has_country_flag = rejected_withdrawing_attache }\n"
		 "\t\t\t\tNOT = { has_country_flag = rejected_withdrawing_attache@ROOT }\n"
		 "\t\t\t\tNOT = { has_country_flag = object_attache_going_on }\n"
		 "\t\t\t}\n"
		 "\t\t\thas_war = yes\n"
		 "\t\t\thas_capitulated = no\n"
		 "\t\t\tNOT = { has_war_with = FROM }\n"
		 "\t\t\tany_enemy_country = {\n"
		 "\t\t\t\thas_attache_from = FROM\n"
		 "\t\t\t}\n"
		 "\t\t}");

	return std::move(objectToAttachesDecision);
}