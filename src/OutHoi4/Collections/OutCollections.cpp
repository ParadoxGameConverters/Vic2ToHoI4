#include "src/OutHoi4/Collections/OutCollections.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/OutHoi4/Collections/OutCollection.h"
#include <fstream>



void HoI4::outputCollections(const std::filesystem::path& outputName, const std::vector<Collection>& collection)
{
	const std::filesystem::path folder = outputName / "common/collections";
	if (!commonItems::DoesFolderExist(folder) && !std::filesystem::create_directories(folder))
	{
		throw std::runtime_error("Could not create " + folder.string());
	}

	const std::filesystem::path file = folder / "ideological_collections.txt";
	std::ofstream out(file);
	if (!out.is_open())
	{
		throw std::runtime_error("Could not create " + file.string());
	}

	for (const auto& collection: collection)
	{
		out << collection << "\n";
	}
}