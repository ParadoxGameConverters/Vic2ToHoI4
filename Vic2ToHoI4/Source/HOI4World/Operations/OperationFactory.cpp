#include "OperationFactory.h"
#include "ParserHelpers.h"



HoI4::Operation::Factory::Factory()
{
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<HoI4::Operation> HoI4::Operation::Factory::getOperation(std::string name, std::istream& theStream)
{
	operation = std::make_unique<Operation>();
	operation->name = std::move(name);

	parseStream(theStream);
	return std::move(operation);
}
