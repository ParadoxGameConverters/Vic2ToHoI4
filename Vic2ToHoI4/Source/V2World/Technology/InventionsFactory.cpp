#include "InventionsFactory.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"



Vic2::Inventions::Factory::Factory()
{
	// invention names have the usual alphanumerics, plus טיצü:&
	registerRegex("[a-zA-Z0-9_.\xe8\xe9\xf6\xfc\\:\\&]+",
		 [this](const std::string& inventionName, std::istream& theStream) {
			 inventions->inventionNames.push_back(inventionName);
			 commonItems::ignoreItem(inventionName, theStream);
		 });
}


std::unique_ptr<Vic2::Inventions> Vic2::Inventions::Factory::loadInventions(const Configuration& theConfiguration)
{
	inventions = std::make_unique<Inventions>();

	const auto inventionFiles = getInventionFiles(theConfiguration);
	generateNumbers(inventionFiles);

	return std::move(inventions);
}


std::vector<std::string> Vic2::Inventions::Factory::getInventionFiles(const Configuration& theConfiguration) const
{
	const auto techFiles = getTechFilesAndPaths(theConfiguration);

	std::vector<std::string> finalTechFiles;
	finalTechFiles.reserve(techFiles.size());
	for (const auto& [filename, path]: techFiles)
	{
		finalTechFiles.push_back(path + filename);
	}

	return finalTechFiles;
}


std::map<std::string, std::string> Vic2::Inventions::Factory::getTechFilesAndPaths(
	 const Configuration& theConfiguration) const
{
	std::map<std::string, std::string> techFiles;

	for (const auto& file: commonItems::GetAllFilesInFolder(theConfiguration.getVic2Path() + "/inventions/"))
	{
		techFiles[file] = theConfiguration.getVic2Path() + "/inventions/";
	}
	for (const auto& mod: theConfiguration.getVic2Mods())
	{
		auto modInventionsPath = theConfiguration.getVic2ModPath() + "/" + mod.getDirectory() + "/inventions/";
		if (commonItems::DoesFolderExist(modInventionsPath))
		{
			for (const auto& file: commonItems::GetAllFilesInFolder(modInventionsPath))
			{
				techFiles[file] = modInventionsPath;
			}
		}
	}

	return techFiles;
}


void Vic2::Inventions::Factory::generateNumbers(const std::vector<std::string>& inventionFiles)
{
	for (const auto& file: inventionFiles)
	{
		parseFile(file);
	}
}