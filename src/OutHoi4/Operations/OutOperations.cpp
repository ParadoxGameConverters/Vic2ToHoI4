#include "src/OutHoi4/Operations/OutOperations.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/OutHoi4/Operations/OutOperation.h"
#include <fstream>



void HoI4::outputOperations(const Operations& operations, const std::filesystem::path& outputName)
{
	const std::filesystem::path folder = "output" / outputName / "common/operations";
	if (!commonItems::DoesFolderExist(folder) && !std::filesystem::create_directories(folder))
	{
		throw std::runtime_error("Could not create " + folder.string());
	}

	const std::filesystem::path file = folder / "00_operations.txt";
	std::ofstream output(file);
	if (!output.is_open())
	{
		throw std::runtime_error("Could not create " + file.string());
	}

	for (const auto& operation: operations.getOperations())
	{
		output << operation;
	}

	output.close();
}