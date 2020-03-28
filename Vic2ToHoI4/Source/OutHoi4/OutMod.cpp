#include "OutMod.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "OutFlags.h"
#include "OutHoi4World.h"
#include <string>



void createModFiles(const std::string& outputName);
void renameOutputFolder(const std::string& outputName);



void clearOutputFolder(const std::string& outputName)
{
	const std::string outputFolder = Utils::getCurrentDirectory() + "/output/" + outputName;
	if (Utils::doesFolderExist(outputFolder))
	{
		if (!Utils::deleteFolder(outputFolder))
		{
			LOG(LogLevel::Error) << "Could not remove pre-existing output folder " << outputFolder
										<< ". Please delete folder and try converting again.";
			exit(-1);
		}
	}
}


void output(HoI4::World& destWorld,
	 const std::string& outputName,
	 bool debugEnabled,
	 const std::vector<std::string>& vic2Mods,
	 const std::string& vic2Path)
{
	createModFiles(outputName);
	renameOutputFolder(outputName);
	copyFlags(destWorld.getCountries(), outputName, vic2Mods, vic2Path);
	HoI4::OutputWorld(destWorld, outputName, debugEnabled);
}


void createModFiles(const std::string& outputName)
{
	LOG(LogLevel::Info) << "Outputting mod";
	if (!Utils::copyFolder("blankMod/output", "output/output"))
	{
		LOG(LogLevel::Error) << "Could not copy blankMod";
		exit(-1);
	}

	std::ofstream modFile("output/" + outputName + ".mod");
	if (!modFile.is_open())
	{
		LOG(LogLevel::Error) << "Could not create .mod file";
		exit(-1);
	}

	modFile << "name = \"Converted - " << outputName << "\"\n";
	modFile << "path = \"mod/" << outputName << "/\"\n";
	modFile << "user_dir = \"" << outputName << "_user_dir\"\n";
	modFile << "replace_path=\"common/ideologies\"\n";
	modFile << "replace_path=\"history/countries\"\n";
	modFile << "replace_path=\"history/states\"\n";
	modFile << "supported_version=\"1.8.1\"";
	modFile.close();

	std::ofstream descriptorFile("output/output/descriptor.mod");
	if (!descriptorFile.is_open())
	{
		LOG(LogLevel::Error) << "Could not create descriptor.mod";
		exit(-1);
	}
	descriptorFile << "name = \"Converted - " << outputName << "\"\n";
	descriptorFile << "user_dir = \"" << outputName << "_user_dir\"\n";
	descriptorFile << "replace_path=\"common/ideologies\"\n";
	descriptorFile << "replace_path=\"history/countries\"\n";
	descriptorFile << "replace_path=\"history/states\"\n";
	descriptorFile << "supported_version=\"1.8.1\"";
	descriptorFile.close();
}


void renameOutputFolder(const std::string& outputName)
{
	if (!Utils::renameFolder("output/output", "output/" + outputName))
	{
		LOG(LogLevel::Error) << "Could not rename output folder!";
		exit(-1);
	}
}