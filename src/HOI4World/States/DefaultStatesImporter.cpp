#include "DefaultStatesImporter.h"
#include "OSCompatibilityLayer.h"
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
	for (const auto& stateFile: commonItems::GetAllFilesInFolder(statesPath.string()))
	{
		num_ = std::stoi(stateFile.substr(0, stateFile.find_first_of('-')));
		const auto filePath = statesPath / stateFile;
		parseFile(filePath.string());
	}

	return defaultStates_;
}