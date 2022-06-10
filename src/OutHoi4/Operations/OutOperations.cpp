#include "src/OutHoi4/Operations/OutOperations.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/OutHoi4/Operations/OutOperation.h"
#include <fstream>



void HoI4::outputOperations(const Operations& operations, const std::string& outputName)
{
	if (!commonItems::TryCreateFolder("output/" + outputName + "/common/operations/"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/common/operations/");
	}
	std::ofstream output("output/" + outputName + "/common/operations/00_operations.txt");
	if (!output.is_open())
	{
		throw std::runtime_error("Could not create output/" + outputName + "/common/operations/00_operations.txt");
	}

	for (const auto& operation: operations.getOperations())
	{
		output << operation;
	}

	output.close();
}