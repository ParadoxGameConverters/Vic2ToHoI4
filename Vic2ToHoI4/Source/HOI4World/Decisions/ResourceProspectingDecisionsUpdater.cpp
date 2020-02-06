#include "ResourceProspectingDecisionsUpdater.h"
#include <functional>
#include <map>
#include <string>



void HoI4::updateResourceProspectingDecisions(
	DecisionsFile& resourceProspectingDecisions,
	const std::map<int, int>& _provinceToStateIdMap
)
{
	std::map<
		std::string,
		std::function<decision(decision&& decisionToUpdate, const std::map<int, int>& provinceToStateIdMap)>
	> decisionsUpdaterMap;
	
	for (auto& category: resourceProspectingDecisions.getDecisions())
	{
		for (auto& decisionToUpdate: category.getDecisions())
		{
			auto name = decisionToUpdate.getName();
			if (auto mapping = decisionsUpdaterMap.find(name); mapping != decisionsUpdaterMap.end())
			{
				category.replaceDecision(mapping->second(std::move(decisionToUpdate), _provinceToStateIdMap));
			}
		}
	}
}