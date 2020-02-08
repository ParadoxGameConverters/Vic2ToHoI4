#include "ResourceProspectingDecisionsUpdater.h"
#include <functional>
#include <map>
#include <string>


// todo: this is duplicated from GenericDecisions.cpp. Move both to a common file
std::set<int> getRelevantStatesFromProvinces2(
	const std::set<int>& provinces,
	const std::set<int>& statesToExclude,
	const std::map<int, int>& provinceToStateIdMap
)
{
	std::set<int> relevantStates;
	for (const auto& province : provinces)
	{
		if (
			auto mapping = provinceToStateIdMap.find(province);
			mapping != provinceToStateIdMap.end() && (statesToExclude.count(mapping->second) == 0)
			)
		{
			relevantStates.insert(mapping->second);
		}
	}

	return relevantStates;
}



HoI4::decision updateDevelopShandongAluminiumDeposits(HoI4::decision&& decisionToUpdate, const std::map<int, int>& provinceToStateIdMap)
{
	int shandongState = *getRelevantStatesFromProvinces2({ 1069 }, {}, provinceToStateIdMap).begin();

	std::string highlightStates = "= {\n";
	highlightStates += "\t\t\tstate = " + std::to_string(shandongState) + "\n";
	highlightStates += "\t\t}\n";
	decisionToUpdate.setHighlightStates(highlightStates);

	std::string available = "= {\n";
	available += "\t\t\thas_tech = excavation3\n";
	available += "\t\t\tnum_of_civilian_factories_available_for_projects > 2\n";
	available += "\t\t\towns_state = " + std::to_string(shandongState) + "\n";
	available += "\t\t\tcontrols_state = " + std::to_string(shandongState) + "\n";
	available += "\t\t}";
	decisionToUpdate.setAvailable(available);

	std::string visible = "= {\n";
	visible += "\t\t\towns_state = " + std::to_string(shandongState) + "\n";
	visible += "\t\t\tcontrols_state = " + std::to_string(shandongState) + "\n";
	visible += "\t\t\t" + std::to_string(shandongState) + " = {\n";
	visible += "\t\t\t\tNOT = {\n";
	visible += "\t\t\t\t\thas_state_flag = shandong_aluminium_developed\n";
	visible += "\t\t\t\t}\n";
	visible += "\t\t\t}\n";
	visible += "\t\t}";
	decisionToUpdate.setVisible(visible);

	std::string removeEffect = "= {\n";
	removeEffect += "\t\t\t" + std::to_string(shandongState) + " = { set_state_flag = shandong_aluminium_developed }\n";
	removeEffect += "\t\t\t" + std::to_string(shandongState) + " = {\n";
	removeEffect += "\t\t\t\tadd_resource = {\n";
	removeEffect += "\t\t\t\t\ttype = aluminium\n";
	removeEffect += "\t\t\t\t\tamount = 12\n";
	removeEffect += "\t\t\t\t}\n";
	removeEffect += "\t\t\t}\n";
	removeEffect += "\t\t}";
	decisionToUpdate.setRemoveEffect(removeEffect);
	
	return std::move(decisionToUpdate);
}


HoI4::decision updateDevelopSuiyuanSteelDeposits(HoI4::decision&& decisionToUpdate, const std::map<int, int>& provinceToStateIdMap)
{
	int suiyuanState = *getRelevantStatesFromProvinces2({ 2087 }, {}, provinceToStateIdMap).begin();

	std::string highlightStates = "= {\n";
	highlightStates += "\t\t\tstate = " + std::to_string(suiyuanState) + "\n";
	highlightStates += "\t\t}\n";
	decisionToUpdate.setHighlightStates(highlightStates);

	std::string available = "= {\n";
	available += "\t\t\thas_tech = excavation2\n";
	available += "\t\t\tnum_of_civilian_factories_available_for_projects > 2\n";
	available += "\t\t\towns_state = " + std::to_string(suiyuanState) + "\n";
	available += "\t\t\tcontrols_state = " + std::to_string(suiyuanState) + "\n";
	available += "\t\t}";
	decisionToUpdate.setAvailable(available);

	std::string visible = "= {\n";
	visible += "\t\t\towns_state = " + std::to_string(suiyuanState) + "\n";
	visible += "\t\t\tcontrols_state = " + std::to_string(suiyuanState) + "\n";
	visible += "\t\t\t" + std::to_string(suiyuanState) + " = {\n";
	visible += "\t\t\t\tNOT = {\n";
	visible += "\t\t\t\t\thas_state_flag = suiyuan_steel_developed\n";
	visible += "\t\t\t\t}\n";
	visible += "\t\t\t}\n";
	visible += "\t\t}";
	decisionToUpdate.setVisible(visible);

	std::string removeEffect = "= {\n";
	removeEffect += "\t\t\t" + std::to_string(suiyuanState) + " = { set_state_flag = suiyuan_steel_developed }\n";
	removeEffect += "\t\t\t" + std::to_string(suiyuanState) + " = {\n";
	removeEffect += "\t\t\t\tadd_resource = {\n";
	removeEffect += "\t\t\t\t\ttype = steel\n";
	removeEffect += "\t\t\t\t\tamount = 8\n";
	removeEffect += "\t\t\t\t}\n";
	removeEffect += "\t\t\t}\n";
	removeEffect += "\t\t}";
	decisionToUpdate.setRemoveEffect(removeEffect);

	return std::move(decisionToUpdate);
}


void HoI4::updateResourceProspectingDecisions(
	DecisionsFile& resourceProspectingDecisions,
	const std::map<int, int>& _provinceToStateIdMap
)
{
	std::map<
		std::string,
		std::function<decision(decision&& decisionToUpdate, const std::map<int, int>& provinceToStateIdMap)>
	> decisionsUpdaterMap;

	decisionsUpdaterMap.insert(
		std::make_pair("develop_shandong_aluminium_deposits", updateDevelopShandongAluminiumDeposits)
	);
	decisionsUpdaterMap.insert(
		std::make_pair("develop_suiyuan_steel_deposits", updateDevelopSuiyuanSteelDeposits)
	);
	
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