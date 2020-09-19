#include "OperativeNamesFactory.h"
#include "OSCompatibilityLayer.h"
#include "OperativeNamesSetFactory.h"



std::unique_ptr<HoI4::OperativeNames> HoI4::OperativeNames::Factory::getOperativeNames(const std::string& HoI4Path)
{
	auto operativeNames = std::make_unique<OperativeNames>();
	OperativeNamesSet::Factory operativeNameSetFactory;

	for (const auto& filename: commonItems::GetAllFilesInFolder(HoI4Path + "/common/units/codenames_operatives"))
	{
		auto operativesNamesSet = operativeNameSetFactory.getOperativeNamesSetFromFile(
			 HoI4Path + "/common/units/codenames_operatives/" + filename);
		operativeNames->operativeNamesSets.insert(
			 std::make_pair(operativesNamesSet->getWrapper(), std::move(*operativesNamesSet)));
	}
	for (const auto& filename: commonItems::GetAllFilesInFolder("DataFiles/CodenamesOperatives"))
	{
		auto operativesNamesSet =
			 operativeNameSetFactory.getOperativeNamesSetFromFile("DataFiles/CodenamesOperatives/" + filename);
		operativeNames->operativeNamesSets.insert(
			 std::make_pair(operativesNamesSet->getWrapper(), std::move(*operativesNamesSet)));
	}

	return operativeNames;
}