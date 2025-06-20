#include "src/HOI4World/Operations/OperationsFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/Operations/OperationFactory.h"



std::unique_ptr<HoI4::Operations> HoI4::Operations::Factory::getOperations()
{
	auto operations = std::make_unique<Operations>();
	Operation::Factory operationFactory;

	registerRegex(commonItems::catchallRegex,
		 [&operationFactory, &operations](const std::string& name, std::istream& theStream) {
			 operations->operations.push_back(*operationFactory.getOperation(name, theStream));
		 });

	parseFile("blankmod/common/operations/00_operations.txt");

	return operations;
}