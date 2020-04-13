/*Copyright (c) 2018 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



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

	std::set<std::string> mainTechFiles;
	Utils::GetAllFilesInFolder(theConfiguration.getVic2Path() + "/inventions/", mainTechFiles);
	std::for_each(mainTechFiles.begin(), mainTechFiles.end(), [&techFiles, &theConfiguration](const std::string& file) {
		techFiles[file] = theConfiguration.getVic2Path() + "/inventions/";
	});

	for (auto mod: theConfiguration.getVic2Mods())
	{
		std::string modInventionsPath = theConfiguration.getVic2Path() + "/mod/" + mod + "/inventions/";
		if (Utils::doesFolderExist(modInventionsPath))
		{
			std::set<std::string> modTechFiles;
			Utils::GetAllFilesInFolder(modInventionsPath, modTechFiles);
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
	registerKeyword(std::regex("[a-zA-Z0-9_\\.\\è\\é\\ö\\ü\\:\\&]+"),
		 [this](const std::string& inventionName, std::istream& theStream) {
			 inventionNumsToNames.insert(make_pair(inventionNumsToNames.size() + 1, inventionName));
			 commonItems::ignoreItem(inventionName, theStream);
		 });

	parseFile(filename);
}


std::optional<std::string> Vic2::inventions::getInventionName(int inventionNum) const
{
	auto inventionName = inventionNumsToNames.find(inventionNum);
	if (inventionName == inventionNumsToNames.end())
	{
		LOG(LogLevel::Warning) << "Invalid invention. Is this using a mod that changed inventions?";
		return {};
	}
	else
	{
		return inventionName->second;
	}
}