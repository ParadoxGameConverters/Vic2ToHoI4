#include "OutOperations.h"
#include "OSCompatibilityLayer.h"
#include "OutOperation.h"
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