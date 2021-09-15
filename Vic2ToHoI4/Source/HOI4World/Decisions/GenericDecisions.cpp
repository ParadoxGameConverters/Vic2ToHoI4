#include "GenericDecisions.h"
#include <algorithm>
#include <array>



namespace HoI4
{
namespace
{

constexpr std::array suezRegionProvinces{
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
};
constexpr std::array aswanAndEasternDesertProvinces{
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
};
constexpr std::array khartoumProvinces{1977, 12725, 2003};
constexpr std::array eritriaAndSomalilandProvinces{
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
};
const int gibraltarProvince = 4135;
constexpr std::array suezCanalProvinces{
	 12049, // north-west suez canal
	 4073,  // south-west suez canal
	 1155,  // north-east suez canal
	 9947	  // south-east suez canal
};
constexpr std::array panamaCanalProvinces{
	 7617 // Panama province
};
constexpr std::array panamaPeninsulaProvinces{
	 10482,
	 7630,
	 7617,
	 4624,
	 1633,
	 4611 // Panama state
};

template <size_t N>
std::set<int> getRelevantStatesFromProvinces(const std::array<int, N>& provinces,
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


decision&& updateBlowSuez(decision&& blowSuezDecision, const std::map<int, int>& provinceToStateIdMap)
{
	auto relevantCanalStates = getRelevantStatesFromProvinces(suezCanalProvinces, {}, provinceToStateIdMap);
	auto relevantOtherStates =
		 getRelevantStatesFromProvinces(suezRegionProvinces, relevantCanalStates, provinceToStateIdMap);
	auto relevantNileStates = getRelevantStatesFromProvinces(aswanAndEasternDesertProvinces, {}, provinceToStateIdMap);
	auto relevantLandRouteStates = getRelevantStatesFromProvinces(khartoumProvinces, {}, provinceToStateIdMap);
	auto relevantSupplyStates = getRelevantStatesFromProvinces(eritriaAndSomalilandProvinces, {}, provinceToStateIdMap);

	std::optional<int> gibraltar;
	if (auto mapping = provinceToStateIdMap.find(gibraltarProvince); mapping != provinceToStateIdMap.end())
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


decision&& updateBlowPanama(decision&& blowPanamaDecision, const std::map<int, int>& provinceToStateIdMap)
{
	auto canalState = getRelevantStatesFromProvinces(panamaCanalProvinces, {}, provinceToStateIdMap);
	auto peninsulaState = getRelevantStatesFromProvinces(panamaPeninsulaProvinces, {}, provinceToStateIdMap);

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


decision&& updateRebuildSuez(decision&& rebuildSuezDecision, const std::map<int, int>& provinceToStateIdMap)
{
	auto relevantCanalStates = getRelevantStatesFromProvinces(suezCanalProvinces, {}, provinceToStateIdMap);

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


decision&& updateRebuildPanama(decision&& rebuildPanamaDecision, const std::map<int, int>& provinceToStateIdMap)
{
	auto canalState = getRelevantStatesFromProvinces(panamaCanalProvinces, {}, provinceToStateIdMap);
	auto peninsulaState = getRelevantStatesFromProvinces(panamaPeninsulaProvinces, canalState, provinceToStateIdMap);

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


decision&& updateWomenInTheWorkforce(decision&& womenInTheWorkforceDecision,
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


decision&& updateWarBonds(decision&& warBondsDecision, const std::set<std::string>& majorIdeologies)
{
	auto available = warBondsDecision.getAvailable();
	for (const auto& [ideology, placeholderText]:
		 std::vector<std::tuple<std::string, std::string>>{
			  {"absolutist", "\t\t\t\t$ABSOLUTIST\n"},
			  {"communism", "\t\t\t\t$COMMUNISM\n"},
			  {"democratic", "\t\t\t\t$DEMOCRATIC\n"},
			  {"fascism", "\t\t\t\t$FASCISM\n"},
			  {"radical", "\t\t\t\t$RADICAL\n"}})
	{
		if (majorIdeologies.contains(ideology))
		{
			std::string ideologyAvailable;
			ideologyAvailable += "\t\t\t\tAND = {\n";
			ideologyAvailable += "\t\t\t\t\thas_government = " + ideology + "\n";
			ideologyAvailable += "\t\t\t\t\thas_war_support > 0.79\n";
			if (ideology == "fascism")
			{
				ideologyAvailable += "\t\t\t\t\tsurrender_progress > 0\n";
			}
			ideologyAvailable += "\t\t\t\t}\n"; 
			while (available.find(placeholderText) != std::string::npos)
			{
				available.replace(available.find(placeholderText), placeholderText.size(), ideologyAvailable);
			} 
		}
		else
		{
			available.replace(available.find(placeholderText), placeholderText.size(), "");
		}
	}
	warBondsDecision.setAvailable(available);

	return std::move(warBondsDecision);
}

} // namespace



void GenericDecisions::updateDecisions(const std::map<int, int>& provinceToStateIdMap,
	 const std::set<std::string>& majorIdeologies)
{
	for (auto& category: decisions)
	{
		if (category.getName() == "economy_decisions")
		{
			auto decisions = category.getDecisions();
			const auto [first, last] = std::ranges::remove_if(decisions, [](auto& decision) {
				return decision.getName() == "dismantle_maginot";
			});
			decisions.erase(first, last);
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
		}
	}

	const auto [first, last] = std::ranges::remove_if(decisions, [](auto& decisionCategory) {
		return decisionCategory.getName() == "foreign_support";
	});
	decisions.erase(first, last);
}

} // namespace HoI4