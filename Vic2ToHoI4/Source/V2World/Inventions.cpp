#include "Inventions.h"
#include "../Configuration.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"



Vic2::inventions::inventions(const Configuration& theConfiguration) noexcept
{
	auto inventionFiles = getInventionFiles(theConfiguration);
	generateNums(inventionFiles);
}


std::list<std::string> Vic2::inventions::getInventionFiles(const Configuration& theConfiguration) const
{
	std::map<std::string, std::string> techFiles;

	auto mainTechFiles = Utils::GetAllFilesInFolder(theConfiguration.getVic2Path() + "/inventions/");
	std::for_each(mainTechFiles.begin(), mainTechFiles.end(), [&techFiles, &theConfiguration](const std::string& file) {
		techFiles[file] = theConfiguration.getVic2Path() + "/inventions/";
	});

	for (const auto& mod: theConfiguration.getVic2Mods())
	{
		std::string modInventionsPath = theConfiguration.getVic2ModPath() + "/" + mod.getDirectory() + "/inventions/";
		if (Utils::DoesFolderExist(modInventionsPath))
		{
			auto modTechFiles = Utils::GetAllFilesInFolder(modInventionsPath);
			std::for_each(modTechFiles.begin(),
				 modTechFiles.end(),
				 [&techFiles, modInventionsPath](const std::string& file) {
					 techFiles[file] = modInventionsPath;
				 });
		}
	}

	std::list<std::string> finalTechFiles;
	std::for_each(techFiles.begin(),
		 techFiles.end(),
		 [&finalTechFiles](const std::pair<std::string, std::string>& file) {
			 finalTechFiles.push_back(file.second + file.first);
		 });

	return finalTechFiles;
}


void Vic2::inventions::generateNums(const std::list<std::string>& inventionFiles)
{
	for (auto file: inventionFiles)
	{
		processTechFile(file);
	}
}


void Vic2::inventions::processTechFile(const std::string& filename)
{
	registerRegex("[a-zA-Z0-9_.טיצü\\:\\&]+", [this](const std::string& inventionName, std::istream& theStream) {
		inventionNumsToNames.insert(make_pair(static_cast<int>(inventionNumsToNames.size()) + 1, inventionName));
		commonItems::ignoreItem(inventionName, theStream);
	});

	parseFile(filename);
}


std::optional<std::string> Vic2::inventions::getInventionName(int inventionNum) const
{
	auto inventionName = inventionNumsToNames.find(inventionNum);
	if (inventionName == inventionNumsToNames.end())
	{
		Log(LogLevel::Warning) << "Invalid invention. Is this using a mod that changed inventions?";
		return {};
	}
	else
	{
		return inventionName->second;
	}
}