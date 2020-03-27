#include "OutMod.h"
#include "../Flags.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "OutHoi4World.h"
#include <string>



void createModFiles();
void renameOutputFolder();



void clearOutputFolder()
{
	const std::string outputFolder = Utils::getCurrentDirectory() + "/output/" + theConfiguration.getOutputName();
	if (Utils::doesFolderExist(outputFolder))
	{
		if (!Utils::deleteFolder(outputFolder))
		{
			LOG(LogLevel::Error) << "Could not remove pre-existing output folder " << output
										<< ". Please delete folder and try converting again.";
			exit(-1);
		}
	}
}


void output(HoI4::World& destWorld)
{
	createModFiles();
	renameOutputFolder();
	copyFlags(destWorld.getCountries());
	HoI4::OutputWorld(destWorld);
}


void createModFiles()
{
	LOG(LogLevel::Info) << "Outputting mod";
	if (!Utils::copyFolder("blankMod/output", "output/output"))
	{
		LOG(LogLevel::Error) << "Could not copy blankMod";
		exit(-1);
	}

	ofstream modFile("output/" + theConfiguration.getOutputName() + ".mod");
	if (!modFile.is_open())
	{
		LOG(LogLevel::Error) << "Could not create .mod file";
		exit(-1);
	}

	modFile << "name = \"Converted - " << theConfiguration.getOutputName() << "\"\n";
	modFile << "path = \"mod/" << theConfiguration.getOutputName() << "/\"\n";
	modFile << "user_dir = \"" << theConfiguration.getOutputName() << "_user_dir\"\n";
	modFile << "replace_path=\"common/ideologies\"\n";
	modFile << "replace_path=\"history/countries\"\n";
	modFile << "replace_path=\"history/states\"\n";
	modFile << "supported_version=\"1.8.1\"";
	modFile.close();

	ofstream descriptorFile("output/output/descriptor.mod");
	if (!descriptorFile.is_open())
	{
		LOG(LogLevel::Error) << "Could not create descriptor.mod";
		exit(-1);
	}
	descriptorFile << "name = \"Converted - " << theConfiguration.getOutputName() << "\"\n";
	descriptorFile << "user_dir = \"" << theConfiguration.getOutputName() << "_user_dir\"\n";
	descriptorFile << "replace_path=\"common/ideologies\"\n";
	descriptorFile << "replace_path=\"history/countries\"\n";
	descriptorFile << "replace_path=\"history/states\"\n";
	descriptorFile << "supported_version=\"1.8.1\"";
	descriptorFile.close();
}


void renameOutputFolder()
{
	if (!Utils::renameFolder("output/output", "output/" + theConfiguration.getOutputName()))
	{
		LOG(LogLevel::Error) << "Could not rename output folder!";
		exit(-1);
	}
}