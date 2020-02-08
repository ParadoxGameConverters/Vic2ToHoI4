#include "ResourceProspectingDecisionsUpdater.h"
#include <functional>
#include <map>
#include <regex>
#include <string>



std::optional<int> getRelevantStateFromOldState(
	const int oldStateNum,
	const std::map<int, int>& provinceToStateIdMap,
	const std::map<int, HoI4::DefaultState>& defaultStates
)
{
	const auto& oldState = defaultStates.find(oldStateNum);
	if (oldState == defaultStates.end())
	{
		return std::nullopt;
	}
	
	auto provinces = oldState->second.getProvinces();
	if (provinces.empty())
	{
		return std::nullopt;
	}

	const auto& mapping = provinceToStateIdMap.find(*provinces.begin());
	if (mapping == provinceToStateIdMap.end())
	{
		return std::nullopt;
	}

	return mapping->second;
}


bool aiWillDoNeedsStripping(const std::string_view decisionName)
{
	return
		decisionName == "develop_nauru_tungsten_deposits" ||
		decisionName == "develop_nigeria_rubber_plantations" ||
		decisionName == "develop_newfoundland_steel" ||
		decisionName == "develop_stalingrad_aluminium_deposits" ||
		decisionName == "develop_kyzyl_tungsten_deposits" ||
		decisionName == "develop_chelyabinsk_steel_deposits" ||
		decisionName == "develop_zlatoust_steel_deposits_1" ||
		decisionName == "develop_zlatoust_steel_deposits_2" ||
		decisionName == "develop_kursk_steel_deposits" ||
		decisionName == "develop_kursk_steel_deposits_2" ||
		decisionName == "develop_kursk_steel_deposits_3" ||
		decisionName == "develop_Belgorod_steel_deposits" ||
		decisionName == "develop_Belgorod_steel_deposits_2" ||
		decisionName == "develop_Belgorod_steel_deposits_3" ||
		decisionName == "develop_uralsk_chromium_deposits_1" ||
		decisionName == "develop_uralsk_chromium_deposits_2" ||
		decisionName == "develop_cornwall_tungsten_deposits_1" ||
		decisionName == "develop_caucasus_tungsten_deposits_1" ||
		decisionName == "develop_caucasus_tungsten_deposits_2";
}


bool allowedNeedsStripping(const std::string_view decisionName)
{
	return
		decisionName == "develop_kirin_aluminium_deposits" ||
		decisionName == "develop_sirte_oil_fields" ||
		decisionName == "develop_benghazi_oil_fields";
}


HoI4::decision updateDecision(
	HoI4::decision&& decisionToUpdate,
	const std::map<int, int>& provinceToStateIdMap,
	const std::map<int, HoI4::DefaultState>& defaultStates
)
{
	auto highlightStates = decisionToUpdate.getHighlightStates();

	std::regex stateNumRegex(".+ (\\d+).*");
	std::smatch match;
	std::regex_search(highlightStates, match, stateNumRegex);
	auto oldStateNum = std::stoi(match[1]);

	auto possibleNewStateNum = getRelevantStateFromOldState(oldStateNum, provinceToStateIdMap, defaultStates);
	if (!possibleNewStateNum)
	{
		return std::move(decisionToUpdate);
	}
	auto newStateNum = *possibleNewStateNum;

	auto newHighlightStates =
		std::regex_replace(
			highlightStates,
			std::regex(std::to_string(oldStateNum)),
			std::to_string(newStateNum)
		);
	decisionToUpdate.setHighlightStates(newHighlightStates);

	if (allowedNeedsStripping(decisionToUpdate.getName()))
	{
		decisionToUpdate.setAllowed("= {\n\n\t\t}");
	}

	auto available = decisionToUpdate.getAvailable();
	auto newAvailable =
		std::regex_replace(
			available,
			std::regex(std::to_string(oldStateNum)),
			std::to_string(newStateNum)
		);
	decisionToUpdate.setAvailable(newAvailable);

	auto visible = decisionToUpdate.getVisible();
	auto newVisible =
		std::regex_replace(
			visible,
			std::regex(std::to_string(oldStateNum)),
			std::to_string(newStateNum)
		);
	decisionToUpdate.setVisible(newVisible);

	auto removeEffect = decisionToUpdate.getRemoveEffect();
	auto newRemoveEffect =
		std::regex_replace(
			removeEffect,
			std::regex(std::to_string(oldStateNum)),
			std::to_string(newStateNum)
		);
	decisionToUpdate.setRemoveEffect(newRemoveEffect);

	if (aiWillDoNeedsStripping(decisionToUpdate.getName()))
	{
		decisionToUpdate.setAiWillDo("= {\n\t\t\tfactor = 1\n\t\t}");
	}
	
	return std::move(decisionToUpdate);
}


void HoI4::updateResourceProspectingDecisions(
	DecisionsFile& resourceProspectingDecisions,
	const std::map<int, int>& _provinceToStateIdMap,
	const std::map<int, DefaultState>& defaultStates
)
{

	for (auto& category: resourceProspectingDecisions.getDecisions())
	{
		for (auto& decisionToUpdate: category.getDecisions())
		{
			category.replaceDecision(updateDecision(std::move(decisionToUpdate), _provinceToStateIdMap, defaultStates));
		}
	}
}