#include "src/HOI4World/States/DefaultStatesImporter.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include <filesystem>



HoI4::DefaultStatesImporter::DefaultStatesImporter()
{
	registerKeyword("state", [this](std::istream& theStream) {
		defaultStates_.emplace(num_, DefaultState(theStream));
	});
}



std::map<int, HoI4::DefaultState> HoI4::DefaultStatesImporter::ImportDefaultStates(
	 const std::filesystem::path& hoi4Path)
{
	const auto statesPath = hoi4Path / "history" / "states";
	for (const auto& stateFile: commonItems::GetAllFilesInFolder(statesPath))
	{
		num_ = std::stoi(stateFile.string().substr(0, stateFile.string().find_first_of('-')));
		const auto filePath = statesPath / stateFile;
		parseFile(filePath);
	}

	return defaultStates_;
}