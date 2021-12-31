#include "ResourceProspectingDecisions.h"
#include <map>
#include <regex>
#include <string>



std::optional<int> getRelevantStateFromOldState(const int oldStateNum,
	 const std::map<int, int>& provinceToStateIdMap,
	 const std::map<int, HoI4::DefaultState>& defaultStates)
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


bool allowedNeedsStripping(const std::string_view decisionName)
{
	return decisionName == "develop_kirin_aluminium_deposits" || decisionName == "develop_sirte_oil_fields" ||
			 decisionName == "develop_benghazi_oil_fields";
}


HoI4::decision updateDecision(HoI4::decision decisionToUpdate,
	 const std::map<int, int>& provinceToStateIdMap,
	 const std::map<int, HoI4::DefaultState>& defaultStates)
{
	auto highlightStates = decisionToUpdate.getHighlightStateTargets();

	std::regex stateNumRegex(".+ (\\d+).*");
	std::smatch match;
	std::regex_search(highlightStates, match, stateNumRegex);
	auto oldStateNum = std::stoi(match[1]);

	auto possibleNewStateNum = getRelevantStateFromOldState(oldStateNum, provinceToStateIdMap, defaultStates);
	if (!possibleNewStateNum)
	{
		return decisionToUpdate;
	}
	auto newStateNum = *possibleNewStateNum;

	auto newHighlightStates =
		 std::regex_replace(highlightStates, std::regex(std::to_string(oldStateNum)), std::to_string(newStateNum));
	decisionToUpdate.setHighlightStateTargets(newHighlightStates);

	if (allowedNeedsStripping(decisionToUpdate.getName()))
	{
		decisionToUpdate.setAllowed("= {\n\n\t\t}");
	}

	auto available = decisionToUpdate.getAvailable();
	auto newAvailable =
		 std::regex_replace(available, std::regex(std::to_string(oldStateNum)), std::to_string(newStateNum));
	decisionToUpdate.setAvailable(newAvailable);

	auto visible = decisionToUpdate.getVisible();
	auto newVisible = std::regex_replace(visible, std::regex(std::to_string(oldStateNum)), std::to_string(newStateNum));
	decisionToUpdate.setVisible(newVisible);

	auto removeEffect = decisionToUpdate.getRemoveEffect();
	auto newRemoveEffect =
		 std::regex_replace(removeEffect, std::regex(std::to_string(oldStateNum)), std::to_string(newStateNum));
	decisionToUpdate.setRemoveEffect(newRemoveEffect);

	return decisionToUpdate;
}


void HoI4::ResourceProspectingDecisions::updateDecisions(const std::map<int, int>& _provinceToStateIdMap,
	 const std::map<int, DefaultState>& defaultStates)
{
	for (auto& category: decisions)
	{
		for (const auto& decisionToUpdate: category.getDecisions())
		{
			category.replaceDecision(updateDecision(decisionToUpdate, _provinceToStateIdMap, defaultStates));
		}
	}
}