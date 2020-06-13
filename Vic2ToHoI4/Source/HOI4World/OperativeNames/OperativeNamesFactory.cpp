#include "OperativeNamesFactory.h"
#include "OSCompatibilityLayer.h"
#include "OperativeNamesSetFactory.h"



std::unique_ptr<HoI4::OperativeNames> HoI4::OperativeNames::Factory::getOperativeNames(
	 const std::string& HoI4Path)
{
	auto operativeNames = std::make_unique<OperativeNames>();
	OperativeNamesSet::Factory operativeNameSetFactory;

	for (const auto& filename: Utils::GetAllFilesInFolder(HoI4Path + "/common/units/codenames_operatives"))
	{
		operativeNames->operativeNamesSets.push_back(std::move(*operativeNameSetFactory.getOperativeNamesSetFromFile(
			 HoI4Path + "/common/units/codenames_operatives/" + filename)));
	}
	for (const auto& filename: Utils::GetAllFilesInFolder("DataFiles/CodenamesOperatives"))
	{
		operativeNames->operativeNamesSets.push_back(std::move(
			 *operativeNameSetFactory.getOperativeNamesSetFromFile("DataFiles/CodenamesOperatives/" + filename)));
	}

	return operativeNames;
}