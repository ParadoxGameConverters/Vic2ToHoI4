#include "GenericDecisions.h"
#include <algorithm>
#include <array>



namespace HoI4
{
namespace
{

constexpr std::array kielCanalProvinces{317, 3231, 11366};

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
constexpr int gibraltarProvince = 4135;
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


std::string createReplacementText(const std::set<int>& states,
	 const std::string& prefix,
	 const std::string& suffix,
	 int amountToTrim)
{
	std::string replacementText;
	for (const auto& state: states)
	{
		replacementText += prefix + std::to_string(state) + suffix;
	}
	replacementText = replacementText.substr(0, replacementText.length() - amountToTrim);

	return replacementText;
}


template <size_t N>
decision&& updateBuildCanal(decision&& buildCanalDecision,
	 const std::array<int, N>& provinces,
	 const std::map<int, int>& provinceToStateIdMap)
{
	const std::string canalStatesPlaceholder = "$CANAL_STATES";
	const auto relevantCanalStates = getRelevantStatesFromProvinces(provinces, {}, provinceToStateIdMap);

	const auto canalFullControlStatesString =
		 createReplacementText(relevantCanalStates, "has_full_control_of_state = ", "\n\t\t\t", 4);
	auto available = buildCanalDecision.getAvailable();
	available.replace(available.find(canalStatesPlaceholder),
		 canalStatesPlaceholder.size(),
		 canalFullControlStatesString);
	buildCanalDecision.setAvailable(available);

	std::string canalControlsStatesString;
	if (relevantCanalStates.size() == 1)
	{
		canalControlsStatesString += createReplacementText(relevantCanalStates, "controls_state = ", "\n\t\t\t", 4);
	}
	else
	{
		canalControlsStatesString = "OR = {\n\t\t\t\t";
		canalControlsStatesString += createReplacementText(relevantCanalStates, "controls_state = ", "\n\t\t\t\t", 5);
		canalControlsStatesString += "\n\t\t\t}";
	}
	auto visible = buildCanalDecision.getVisible();
	visible.replace(visible.find(canalStatesPlaceholder),
		canalStatesPlaceholder.size(),
		canalControlsStatesString);
	buildCanalDecision.setVisible(visible);

	return std::move(buildCanalDecision);
}


decision&& updateBlowSuez(decision&& blowSuezDecision, const std::map<int, int>& provinceToStateIdMap)
{
	// define placeholders
	const std::string canalStatesPlaceholder = "$CANAL_STATES";
	const std::string otherStatesPlaceholder = "$OTHER_STATES";
	const std::string twoDivisionsInStatesPlaceholder = "$TWO_DIVISIONS_IN_STATES";
	const std::string nileStatesPlaceholder = "$NILE_STATES";
	const std::string landRoutesStatesPlaceholder = "$LAND_ROUTE_STATES";
	const std::string supplyStatesPlaceholder = "$SUPPLY_STATES";

	// sets of states and provinces
	const auto relevantCanalStates = getRelevantStatesFromProvinces(suezCanalProvinces, {}, provinceToStateIdMap);
	const auto relevantOtherStates =
		 getRelevantStatesFromProvinces(suezRegionProvinces, relevantCanalStates, provinceToStateIdMap);
	const auto relevantNileStates =
		 getRelevantStatesFromProvinces(aswanAndEasternDesertProvinces, {}, provinceToStateIdMap);
	const auto relevantLandRouteStates = getRelevantStatesFromProvinces(khartoumProvinces, {}, provinceToStateIdMap);
	const auto relevantSupplyStates =
		 getRelevantStatesFromProvinces(eritriaAndSomalilandProvinces, {}, provinceToStateIdMap);

	std::optional<int> gibraltar;
	if (const auto mapping = provinceToStateIdMap.find(gibraltarProvince); mapping != provinceToStateIdMap.end())
	{
		gibraltar = mapping->second;
	}

	// update available block
	auto available = blowSuezDecision.getAvailable();

	const auto canalControlStatesString = createReplacementText(relevantCanalStates, "controls_state = ", "\n\t\t\t", 4);
	available.replace(available.find(canalStatesPlaceholder), canalStatesPlaceholder.size(), canalControlStatesString);

	auto canalOwnsStateString = createReplacementText(relevantCanalStates, "owns_state = ", "\n\t\t\t\t\t", 6);
	available.replace(available.find(canalStatesPlaceholder), canalStatesPlaceholder.size(), canalOwnsStateString);

	auto otherStatesString = createReplacementText(relevantOtherStates, "controls_state = ", "\n\t\t\t\t\t\t", 7);
	available.replace(available.find(otherStatesPlaceholder), otherStatesPlaceholder.size(), otherStatesString);

	blowSuezDecision.setAvailable(available);

	// update complete_effect block
	canalOwnsStateString = createReplacementText(relevantCanalStates, "owns_state = ", "\n\t\t\t\t\t\t\t", 8);

	std::string completeEffect = blowSuezDecision.getCompleteEffect();
	completeEffect.replace(completeEffect.find(canalStatesPlaceholder),
		 canalStatesPlaceholder.size(),
		 canalOwnsStateString);
	completeEffect.replace(completeEffect.find(canalStatesPlaceholder),
		 canalStatesPlaceholder.size(),
		 canalOwnsStateString);

	blowSuezDecision.setCompleteEffect(completeEffect);

	// update remove_effect block
	std::string canalFullControlStatesString =
		 createReplacementText(relevantCanalStates, "has_full_control_of_state = ", "\n\t\t\t\t\t\t", 7);

	std::string removeEffect = blowSuezDecision.getRemoveEffect();
	removeEffect.replace(removeEffect.find(canalStatesPlaceholder),
		 canalStatesPlaceholder.size(),
		 canalFullControlStatesString);

	blowSuezDecision.setRemoveEffect(removeEffect);

	// update ai_will_do
	std::string aiWillDo = blowSuezDecision.getAiWillDo();

	otherStatesString = createReplacementText(relevantOtherStates, "controls_state = ", "\n\t\t\t\t\t\t\t", 8);
	aiWillDo.replace(aiWillDo.find(otherStatesPlaceholder), otherStatesPlaceholder.size(), otherStatesString);

	const auto twoDivisionsInStateString = createReplacementText(relevantOtherStates,
		 "divisions_in_state = { state = ",
		 " size > 2 }\n\t\t\t\t\t\t\t\t",
		 9);
	aiWillDo.replace(aiWillDo.find(twoDivisionsInStatesPlaceholder),
		 twoDivisionsInStatesPlaceholder.size(),
		 twoDivisionsInStateString);

	const auto nileStatesString =
		 createReplacementText(relevantNileStates, "has_full_control_of_state = ", "\n\t\t\t\t\t\t\t", 8);
	aiWillDo.replace(aiWillDo.find(nileStatesPlaceholder), nileStatesPlaceholder.size(), nileStatesString);

	const auto landRoutesStatesString =
		 createReplacementText(relevantLandRouteStates, "NOT = { has_full_control_of_state = ", " }\n\t\t\t\t\t", 6);
	aiWillDo.replace(aiWillDo.find(landRoutesStatesPlaceholder),
		 landRoutesStatesPlaceholder.size(),
		 landRoutesStatesString);

	const auto supplyStatesString =
		 createReplacementText(relevantSupplyStates, "divisions_in_state = { state = ", " size > 0 }\n\t\t\t\t\t\t", 7);
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

	const auto canalStates = getRelevantStatesFromProvinces(panamaCanalProvinces, {}, provinceToStateIdMap);
	const auto peninsulaStates = getRelevantStatesFromProvinces(panamaPeninsulaProvinces, {}, provinceToStateIdMap);

	const auto canalControlStatesString =
		 createReplacementText(canalStates, "has_full_control_of_state = ", "\n\t\t\t", 4);
	auto available = blowPanamaDecision.getAvailable();
	available.replace(available.find(canalStatesPlaceholder), canalStatesPlaceholder.size(), canalControlStatesString);
	blowPanamaDecision.setAvailable(available);

	const auto canalOwnershipStatesString = createReplacementText(canalStates, "owns_state = ", "\n\t\t\t", 4);
	auto completeEffect = blowPanamaDecision.getCompleteEffect();
	completeEffect.replace(completeEffect.find(canalStatesPlaceholder),
		 canalStatesPlaceholder.size(),
		 canalOwnershipStatesString);
	completeEffect.replace(completeEffect.find(canalStatesPlaceholder),
		 canalStatesPlaceholder.size(),
		 canalOwnershipStatesString);
	blowPanamaDecision.setCompleteEffect(completeEffect);

	const auto peninsulaStatesString =
		 createReplacementText(peninsulaStates, "has_full_control_of_state = ", "\n\t\t\t\t\t\t", 7);
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

	const auto canalStates = getRelevantStatesFromProvinces(suezCanalProvinces, {}, provinceToStateIdMap);
	auto canalStatesString = createReplacementText(canalStates, "has_full_control_of_state = ", "\n\t\t\t", 4);

	auto available = rebuildSuezDecision.getAvailable();
	available.replace(available.find(canalStatesPlaceholder), canalStatesPlaceholder.size(), canalStatesString);
	rebuildSuezDecision.setAvailable(available);

	canalStatesString = createReplacementText(canalStates, "has_full_control_of_state = ", "\n\t\t\t\t\t", 6);
	auto removeEffect = rebuildSuezDecision.getRemoveEffect();
	removeEffect.replace(removeEffect.find(canalStatesPlaceholder), canalStatesPlaceholder.size(), canalStatesString);
	rebuildSuezDecision.setRemoveEffect(removeEffect);

	return std::move(rebuildSuezDecision);
}


decision&& updateRebuildPanama(decision&& rebuildPanamaDecision, const std::map<int, int>& provinceToStateIdMap)
{
	const std::string canalStatesPlaceholder = "$CANAL_STATES";
	const std::string peninsulaStatesPlaceholder = "$PENINSULA_STATES";

	const auto canalStates = getRelevantStatesFromProvinces(panamaCanalProvinces, {}, provinceToStateIdMap);
	const auto peninsulaStates =
		 getRelevantStatesFromProvinces(panamaPeninsulaProvinces, canalStates, provinceToStateIdMap);

	const auto canalStatesString = createReplacementText(canalStates, "has_full_control_of_state = ", "\n\t\t\t", 4);
	const auto peninsulaStatesString = createReplacementText(peninsulaStates, "controls_state = ", "\n\t\t\t\t", 5);

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
			if (decision.getName() == "build_kiel_canal")
			{
				category.replaceDecision(updateBuildCanal(std::move(decision), kielCanalProvinces, provinceToStateIdMap));
			}
			else if (decision.getName() == "build_suez_canal")
			{
				category.replaceDecision(updateBuildCanal(std::move(decision), suezCanalProvinces, provinceToStateIdMap));
			}
			else if (decision.getName() == "build_panama_canal")
			{
				category.replaceDecision(updateBuildCanal(std::move(decision), panamaCanalProvinces, provinceToStateIdMap));
			}
			else if (decision.getName() == "blow_suez_canal")
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