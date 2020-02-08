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


HoI4::decision updateDecision(
	HoI4::decision&& decisionToUpdate,
	const std::map<int, int>& provinceToStateIdMap,
	const std::map<int, HoI4::DefaultState>& defaultStates
)
{
	std::string highlightStates = decisionToUpdate.getHighlightStates();

	std::regex stateNumRegex(".+ (\\d+).*");
	std::smatch match;
	std::regex_search(highlightStates, match, stateNumRegex);
	int oldStateNum = std::stoi(match[1]);

	auto possibleNewStateNum = getRelevantStateFromOldState(oldStateNum, provinceToStateIdMap, defaultStates);
	if (!possibleNewStateNum)
	{
		return std::move(decisionToUpdate);
	}
	auto newStateNum = *possibleNewStateNum;

	std::string newHightlightStates = 
		std::regex_replace(
			highlightStates,
			std::regex(std::to_string(oldStateNum)),
			std::to_string(newStateNum)
		);
	decisionToUpdate.setHighlightStates(newHightlightStates);

	std::string available = decisionToUpdate.getAvailable();
	std::string newAvailable =
		std::regex_replace(
			available,
			std::regex(std::to_string(oldStateNum)),
			std::to_string(newStateNum)
		);
	decisionToUpdate.setAvailable(newAvailable);

	std::string visible = decisionToUpdate.getVisible();
	std::string newVisible =
		std::regex_replace(
			visible,
			std::regex(std::to_string(oldStateNum)),
			std::to_string(newStateNum)
		);
	decisionToUpdate.setVisible(newVisible);

	std::string removeEffect = decisionToUpdate.getRemoveEffect();
	std::string newRemoveEffect =
		std::regex_replace(
			removeEffect,
			std::regex(std::to_string(oldStateNum)),
			std::to_string(newStateNum)
		);
	decisionToUpdate.setRemoveEffect(newRemoveEffect);
	
	return std::move(decisionToUpdate);
}


void HoI4::updateResourceProspectingDecisions(
	DecisionsFile& resourceProspectingDecisions,
	const std::map<int, int>& _provinceToStateIdMap,
	const std::map<int, HoI4::DefaultState>& defaultStates
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