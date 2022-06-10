#include "src/OutHoi4/OutMod.h"
#include "external/common_items/Log.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/OutHoi4/OutFlags.h"
#include "src/OutHoi4/OutHoi4World.h"
#include <string>



void createOutputFolder(const std::string& outputName);
void createModFiles(const std::string& outputName);



void clearOutputFolder(const std::string& outputName)
{
	const auto outputFolder = "output/" + outputName;
	if (commonItems::DoesFolderExist(outputFolder))
	{
		Log(LogLevel::Info) << "Removing pre-existing copy of " << outputName;
		if (!commonItems::DeleteFolder(outputFolder))
		{
			throw std::runtime_error("Could not remove pre-existing output folder " + outputFolder +
											 ". Please delete folder and try converting again.");
		}
	}
}


void output(const HoI4::World& destWorld,
	 const std::string& outputName,
	 const bool debugEnabled,
	 const Mods& vic2Mods,
	 const Configuration& theConfiguration)
{
	Log(LogLevel::Progress) << "80%";
	Log(LogLevel::Info) << "Outputting mod";

	createOutputFolder(outputName);
	createModFiles(outputName);
	Log(LogLevel::Progress) << "85%";
	copyFlags(destWorld.getCountries(), outputName, vic2Mods, destWorld.getMajorIdeologies());
	Log(LogLevel::Progress) << "90%";
	OutputWorld(destWorld, outputName, debugEnabled, theConfiguration);
}


void createOutputFolder(const std::string& outputName)
{
	Log(LogLevel::Info) << "\tCopying blank mod";
	if (!commonItems::TryCreateFolder("output"))
	{
		throw std::runtime_error("Could not create output folder");
	}
	if (!commonItems::CopyFolder("blankmod", "output/" + outputName))
	{
		throw std::runtime_error("Could not copy blankMod");
	}
}


void createModFiles(const std::string& outputName)
{
	Log(LogLevel::Info) << "\tCreating .mod files";

	std::ofstream modFile("output/" + outputName + ".mod");
	if (!modFile.is_open())
	{
		throw std::runtime_error("Could not create .mod file");
	}
	modFile << "name = \"Converted - " << outputName << "\"\n";
	modFile << "path = \"mod/" << outputName << "/\"\n";
	modFile << "user_dir = \"" << outputName << "_user_dir\"\n";
	modFile << "replace_path=\"common/ideologies\"\n";
	modFile << "replace_path=\"history/countries\"\n";
	modFile << "replace_path=\"history/states\"\n";
	modFile << "supported_version=\"1.11.*\"";
	modFile.close();

	std::ofstream descriptorFile("output/" + outputName + "/descriptor.mod");
	if (!descriptorFile.is_open())
	{
		throw std::runtime_error("Could not create descriptor.mod");
	}
	descriptorFile << "name = \"Converted - " << outputName << "\"\n";
	descriptorFile << "replace_path=\"common/ideologies\"\n";
	descriptorFile << "replace_path=\"history/countries\"\n";
	descriptorFile << "replace_path=\"history/states\"\n";
	descriptorFile << "supported_version=\"1.11.*\"";
	descriptorFile.close();
}