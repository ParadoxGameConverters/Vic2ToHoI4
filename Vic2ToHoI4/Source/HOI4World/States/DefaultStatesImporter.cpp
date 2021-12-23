#include "DefaultStatesImporter.h"
#include "OSCompatibilityLayer.h"



HoI4::DefaultStatesImporter::DefaultStatesImporter()
{
	registerKeyword("state", [this](std::istream& theStream) {
		defaultStates_.insert(std::make_pair(num_, DefaultState(theStream)));
	});
}



std::map<int, HoI4::DefaultState> HoI4::DefaultStatesImporter::ImportDefaultStates(const std::string& hoi4Path)
{
	const std::string path = hoi4Path + "/history/states";
	for (const auto& stateFile: commonItems::GetAllFilesInFolder(path))
	{
		num_ = std::stoi(stateFile.substr(0, stateFile.find_first_of('-')));
		parseFile(path + stateFile);
	}

	return defaultStates_;
}