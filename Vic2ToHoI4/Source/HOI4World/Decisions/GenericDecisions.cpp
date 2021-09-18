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
	const std::string canalStatesPlaceholder = "$CANAL_STATES";
	const std::string otherStatesPlaceholder = "$OTHER_STATES";
	const std::string twoDivisionsInStatesPlaceholder = "$TWO_DIVISIONS_IN_STATES";
	const std::string nileStatesPlaceholder = "$NILE_STATES";
	const std::string landRoutesStatesPlaceholder = "$LAND_ROUTE_STATES";
	const std::string supplyStatesPlaceholder = "$SUPPLY_STATES";

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

	std::string canalControlStatesString;
	for (const auto& state: relevantCanalStates)
	{
		canalControlStatesString += "controls_state = " + std::to_string(state) + "\n\t\t\t";
	}
	canalControlStatesString = canalControlStatesString.substr(0, canalControlStatesString.length() - 4);

	std::string canalOwnsStateString;
	for (const auto& state: relevantCanalStates)
	{
		canalOwnsStateString += "owns_state = " + std::to_string(state) + "\n\t\t\t\t\t";
	}
	canalOwnsStateString = canalOwnsStateString.substr(0, canalOwnsStateString.length() - 6);

	std::string otherStatesString;
	for (const auto& state: relevantOtherStates)
	{
		otherStatesString += "controls_state = " + std::to_string(state) + "\n\t\t\t\t\t\t";
	}
	otherStatesString = otherStatesString.substr(0, otherStatesString.length() - 7);

	auto available = blowSuezDecision.getAvailable();
	available.replace(available.find(canalStatesPlaceholder), canalStatesPlaceholder.size(), canalControlStatesString);
	available.replace(available.find(canalStatesPlaceholder), canalStatesPlaceholder.size(), canalOwnsStateString);
	available.replace(available.find(otherStatesPlaceholder), otherStatesPlaceholder.size(), otherStatesString);
	blowSuezDecision.setAvailable(available);

	canalOwnsStateString.clear();
	for (const auto& state: relevantCanalStates) 
	{
		canalOwnsStateString += "owns_state = " + std::to_string(state) + "\n\t\t\t\t\t\t\t";
	}
	canalOwnsStateString = canalOwnsStateString.substr(0, canalOwnsStateString.length() - 8);
	std::string completeEffect = blowSuezDecision.getCompleteEffect();
	completeEffect.replace(completeEffect.find(canalStatesPlaceholder),
		 canalStatesPlaceholder.size(),
		 canalOwnsStateString);
	completeEffect.replace(completeEffect.find(canalStatesPlaceholder),
		 canalStatesPlaceholder.size(),
		 canalOwnsStateString);
	blowSuezDecision.setCompleteEffect(completeEffect);

	std::string canalFullControlStatesString;
	for (const auto& state: relevantCanalStates)
	{
		canalFullControlStatesString += "has_full_control_of_state = " + std::to_string(state) + "\n\t\t\t\t\t\t";
	}
	canalFullControlStatesString = canalFullControlStatesString.substr(0, canalFullControlStatesString.length() - 7);

	std::string removeEffect = blowSuezDecision.getRemoveEffect();
	removeEffect.replace(removeEffect.find(canalStatesPlaceholder),
		 canalStatesPlaceholder.size(),
		 canalFullControlStatesString);
	blowSuezDecision.setRemoveEffect(removeEffect);

	std::string aiWillDo = blowSuezDecision.getAiWillDo();
	otherStatesString.clear();
	for (const auto& state: relevantOtherStates)
	{
		otherStatesString += "controls_state = " + std::to_string(state) + "\n\t\t\t\t\t\t\t";
	}
	otherStatesString = otherStatesString.substr(0, otherStatesString.length() - 8);
	aiWillDo.replace(aiWillDo.find(otherStatesPlaceholder), otherStatesPlaceholder.size(), otherStatesString);
	std::string twoDivisionsInStateString;
	for (const auto& state: relevantOtherStates)
	{
		twoDivisionsInStateString += "divisions_in_state = { state = " + std::to_string(state) + " size > 2 }\n\t\t\t\t\t\t\t\t";
	}
	twoDivisionsInStateString = twoDivisionsInStateString.substr(0, twoDivisionsInStateString.length() - 9);
	aiWillDo.replace(aiWillDo.find(twoDivisionsInStatesPlaceholder),
		 twoDivisionsInStatesPlaceholder.size(),
		 twoDivisionsInStateString);
	std::string nileStatesString;
	for (const auto& state: relevantNileStates)
	{
		nileStatesString +=
			 "has_full_control_of_state = " + std::to_string(state) + "\n\t\t\t\t\t\t\t";
	}
	nileStatesString = nileStatesString.substr(0, nileStatesString.length() - 8);
	aiWillDo.replace(aiWillDo.find(nileStatesPlaceholder), nileStatesPlaceholder.size(), nileStatesString);
	std::string landRoutesStatesString;
	for (const auto& state: relevantLandRouteStates)
	{
		landRoutesStatesString += "NOT = { has_full_control_of_state = " + std::to_string(state) + " }\n\t\t\t\t\t";
	}
	landRoutesStatesString = landRoutesStatesString.substr(0, landRoutesStatesString.length() - 6);
	aiWillDo.replace(aiWillDo.find(landRoutesStatesPlaceholder),
		 landRoutesStatesPlaceholder.size(),
		 landRoutesStatesString);
	std::string supplyStatesString;
	for (const auto& state: relevantSupplyStates)
	{
		supplyStatesString += "divisions_in_state = { state = " + std::to_string(state) + " size > 0 }\n\t\t\t\t\t\t";
	}
	supplyStatesString = supplyStatesString.substr(0, supplyStatesString.length() - 7);
	aiWillDo.replace(aiWillDo.find(supplyStatesPlaceholder), supplyStatesPlaceholder.size(), supplyStatesString);
	if (gibraltar)
	{
		aiWillDo = aiWillDo.substr(0, aiWillDo.length() - 3);
		aiWillDo += "\t\t\tmodifier = {\n";
		aiWillDo +=
			 "\t\t\t\tfactor = 200 # Try to cut the enemy off from the mediterranean if you also occupy Gibraltar\n";
		aiWillDo += "\t\t\t\tOR = {\n";
		aiWillDo += "\t\t\t\t\thas_full_control_of_state = " + std::to_string(*gibraltar) + "\n";
		aiWillDo += "\t\t\t\t\tany_allied_country = {\n";
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
	const std::string canalStatesPlaceholder = "$CANAL_STATES";
	const std::string peninsulaStatesPlaceholder = "$PENINSULA_STATES";

	auto canalStates = getRelevantStatesFromProvinces(panamaCanalProvinces, {}, provinceToStateIdMap);
	auto peninsulaStates = getRelevantStatesFromProvinces(panamaPeninsulaProvinces, {}, provinceToStateIdMap);

	std::string canalControlStatesString;
	for (const auto& state: canalStates)
	{
		canalControlStatesString += "has_full_control_of_state = " + std::to_string(state) + "\n\t\t\t";
	}
	canalControlStatesString = canalControlStatesString.substr(0, canalControlStatesString.length() - 4);

	auto available = blowPanamaDecision.getAvailable();
	available.replace(available.find(canalStatesPlaceholder), canalStatesPlaceholder.size(), canalControlStatesString);
	blowPanamaDecision.setAvailable(available);

	std::string canalOwnershipStatesString;
	for (const auto& state: canalStates)
	{
		canalOwnershipStatesString += "owns_state = " + std::to_string(state) + "\n\t\t\t";
	}
	canalOwnershipStatesString = canalOwnershipStatesString.substr(0, canalOwnershipStatesString.length() - 4);
	auto completeEffect = blowPanamaDecision.getCompleteEffect();
	completeEffect.replace(completeEffect.find(canalStatesPlaceholder),
		 canalStatesPlaceholder.size(),
		 canalOwnershipStatesString);
	completeEffect.replace(completeEffect.find(canalStatesPlaceholder),
		 canalStatesPlaceholder.size(),
		 canalOwnershipStatesString);
	blowPanamaDecision.setCompleteEffect(completeEffect);

	std::string peninsulaStatesString;
	for (const auto& state: peninsulaStates)
	{
		peninsulaStatesString += "has_full_control_of_state = " + std::to_string(state) + "\n\t\t\t\t\t\t";
	}
	peninsulaStatesString = peninsulaStatesString.substr(0, peninsulaStatesString.length() - 7);

	auto removeEffect = blowPanamaDecision.getRemoveEffect();
	removeEffect.replace(removeEffect.find(peninsulaStatesPlaceholder),
		 peninsulaStatesPlaceholder.size(),
		 peninsulaStatesString);
	blowPanamaDecision.setRemoveEffect(removeEffect);

	return std::move(blowPanamaDecision);
}


decision&& updateRebuildSuez(decision&& rebuildSuezDecision, const std::map<int, int>& provinceToStateIdMap)
{
	const std::string canalStatesPlaceholder = "$CANAL_STATES";

	auto canalStates = getRelevantStatesFromProvinces(suezCanalProvinces, {}, provinceToStateIdMap);
	std::string canalStatesString;
	for (const auto& state: canalStates)
	{
		canalStatesString += "has_full_control_of_state = " + std::to_string(state) + "\n\t\t\t";
	}
	canalStatesString = canalStatesString.substr(0, canalStatesString.length() - 4);

	auto available = rebuildSuezDecision.getAvailable();
	available.replace(available.find(canalStatesPlaceholder), canalStatesPlaceholder.size(), canalStatesString);
	rebuildSuezDecision.setAvailable(available);

	canalStatesString.clear();
	for (const auto& state: canalStates)
	{
		canalStatesString += "has_full_control_of_state = " + std::to_string(state) + "\n\t\t\t\t\t";
	}
	canalStatesString = canalStatesString.substr(0, canalStatesString.length() - 6);
	std::string removeEffect = rebuildSuezDecision.getRemoveEffect();
	removeEffect.replace(removeEffect.find(canalStatesPlaceholder), canalStatesPlaceholder.size(), canalStatesString);
	rebuildSuezDecision.setRemoveEffect(removeEffect);

	return std::move(rebuildSuezDecision);
}


decision&& updateRebuildPanama(decision&& rebuildPanamaDecision, const std::map<int, int>& provinceToStateIdMap)
{
	const std::string canalStatesPlaceholder = "$CANAL_STATES";
	const std::string peninsulaStatesPlaceholder = "$PENINSULA_STATES";

	auto canalStates = getRelevantStatesFromProvinces(panamaCanalProvinces, {}, provinceToStateIdMap);
	auto peninsulaStates = getRelevantStatesFromProvinces(panamaPeninsulaProvinces, canalStates, provinceToStateIdMap);

	std::string canalStatesString;
	for (const auto& state: canalStates)
	{
		canalStatesString += "has_full_control_of_state = " + std::to_string(state) + "\n\t\t\t";
	}
	canalStatesString = canalStatesString.substr(0, canalStatesString.length() - 4);

	std::string peninsulaStatesString;
	for (const auto& state: peninsulaStates)
	{
		peninsulaStatesString += "controls_state = " + std::to_string(state) + "\n\t\t\t\t";
	}
	peninsulaStatesString = peninsulaStatesString.substr(0, peninsulaStatesString.length() - 5);

	auto available = rebuildPanamaDecision.getAvailable();
	available.replace(available.find(canalStatesPlaceholder), canalStatesPlaceholder.size(), canalStatesString);
	available.replace(available.find(peninsulaStatesPlaceholder),
		 peninsulaStatesPlaceholder.size(),
		 peninsulaStatesString);
	rebuildPanamaDecision.setAvailable(available);

	std::string removeEffect = rebuildPanamaDecision.getRemoveEffect();
	removeEffect.replace(removeEffect.find(canalStatesPlaceholder), canalStatesPlaceholder.size(), canalStatesString);
	removeEffect.replace(removeEffect.find(peninsulaStatesPlaceholder),
		 peninsulaStatesPlaceholder.size(),
		 peninsulaStatesString);
	rebuildPanamaDecision.setRemoveEffect(removeEffect);

	return std::move(rebuildPanamaDecision);
}


decision&& updateWomenInTheWorkforce(decision&& womenInTheWorkforceDecision,
	 const std::set<std::string>& majorIdeologies)
{
	std::string available = womenInTheWorkforceDecision.getAvailable();
	for (const auto& [ideology, placeholderText]:
		 std::vector<std::tuple<std::string, std::string>>{{"absolutist", "\t\t\t\t$ABSOLUTIST\n"},
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
	womenInTheWorkforceDecision.setAvailable(available);

	return std::move(womenInTheWorkforceDecision);
}


decision&& updateWarBonds(decision&& warBondsDecision, const std::set<std::string>& majorIdeologies)
{
	auto available = warBondsDecision.getAvailable();
	for (const auto& [ideology, placeholderText]:
		 std::vector<std::tuple<std::string, std::string>>{{"absolutist", "\t\t\t\t$ABSOLUTIST\n"},
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