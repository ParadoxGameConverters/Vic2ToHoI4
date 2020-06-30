#include "OperationsFactory.h"
#include "ParserHelpers.h"



std::unique_ptr<HoI4::Operations> HoI4::Operations::Factory::getOperations(const std::string& HoI4Path)
{
	auto operations = std::make_unique<Operations>();

	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseFile(HoI4Path + "/common/operations/00_operations.txt");

	return operations;
}