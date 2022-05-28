#include "OperationsFactory.h"
#include "CommonRegexes.h"
#include "OperationFactory.h"
#include "ParserHelpers.h"



std::unique_ptr<HoI4::Operations> HoI4::Operations::Factory::getOperations(const std::string& HoI4Path)
{
	auto operations = std::make_unique<Operations>();
	Operation::Factory operationFactory;

	registerRegex(commonItems::catchallRegex,
		 [&operationFactory, &operations](const std::string& name, std::istream& theStream) {
			 operations->operations.push_back(*operationFactory.getOperation(name, theStream));
		 });

	parseFile(HoI4Path + "/common/operations/00_operations.txt");

	return operations;
}