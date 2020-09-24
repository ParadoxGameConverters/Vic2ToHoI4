#include "InventionsFactory.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"


Vic2::Inventions::Factory::Factory()
{
	registerRegex("[a-zA-Z0-9_.טיצü\\:\\&]+", [this](const std::string& inventionName, std::istream& theStream) {
		inventions->inventionNames.push_back(inventionName);
		commonItems::ignoreItem(inventionName, theStream);
	});
}


std::unique_ptr<Vic2::Inventions> Vic2::Inventions::Factory::getInventions(const Configuration& theConfiguration)
{
	inventions = std::make_unique<Inventions>();

	auto inventionFiles = getInventionFiles(theConfiguration);
	generateNums(inventionFiles);

	return std::move(inventions);
}


std::list<std::string> Vic2::Inventions::Factory::getInventionFiles(const Configuration& theConfiguration) const
{
	std::map<std::string, std::string> techFiles;

	auto mainTechFiles = commonItems::GetAllFilesInFolder(theConfiguration.getVic2Path() + "/inventions/");
	std::for_each(mainTechFiles.begin(), mainTechFiles.end(), [&techFiles, &theConfiguration](const std::string& file) {
		techFiles[file] = theConfiguration.getVic2Path() + "/inventions/";
	});

	for (const auto& mod: theConfiguration.getVic2Mods())
	{
		std::string modInventionsPath = theConfiguration.getVic2ModPath() + "/" + mod.getDirectory() + "/inventions/";
		if (commonItems::DoesFolderExist(modInventionsPath))
		{
			auto modTechFiles = commonItems::GetAllFilesInFolder(modInventionsPath);
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


void Vic2::Inventions::Factory::generateNums(const std::list<std::string>& inventionFiles)
{
	for (auto file: inventionFiles)
	{
		processTechFile(file);
	}
}


void Vic2::Inventions::Factory::processTechFile(const std::string& filename)
{


	parseFile(filename);
}