#include "Configuration.h"
#include "HOI4World/HoI4World.h"
#include "Log.h"
#include "Mappers/Provinces/ProvinceMapper.h"
#include "OSCompatibilityLayer.h"
#include "OutHoi4/OutMod.h"
#include "V2World/Vic2Localisations.h"
#include "V2World/World.h"
#include <algorithm>
#include <stdexcept>



void checkMods(const Configuration& theConfiguration);
void setOutputName(const std::string& V2SaveFileName, Configuration& theConfiguration);
void ConvertV2ToHoI4(const std::string& V2SaveFileName)
{
	const auto theConfiguration = Configuration::Factory{}.importConfiguration("configuration.txt");
	checkMods(*theConfiguration);
	setOutputName(V2SaveFileName, *theConfiguration);
	clearOutputFolder(theConfiguration->getOutputName());

	const mappers::ProvinceMapper provinceMapper = mappers::ProvinceMapper::Parser{}.initializeMapper(*theConfiguration);

	Vic2::World sourceWorld(V2SaveFileName, provinceMapper, *theConfiguration);
	HoI4::World destWorld(&sourceWorld, provinceMapper, *theConfiguration);

	output(destWorld,
		 theConfiguration->getOutputName(),
		 theConfiguration->getDebug(),
		 theConfiguration->getVic2Mods(),
		 theConfiguration->getVic2Path(),
		 *theConfiguration);
	LOG(LogLevel::Info) << "* Conversion complete *";
}


void checkMods(const Configuration& theConfiguration)
{
	LOG(LogLevel::Info) << "Double-checking Vic2 mods";

	std::set<std::string> fileNames;
	Utils::GetAllFilesInFolder(theConfiguration.getVic2Path() + "/mod", fileNames);
	for (auto fileName: fileNames)
	{
		const int lastPeriodPos = fileName.find_last_of('.');
		if ((lastPeriodPos != std::string::npos) && (fileName.substr(lastPeriodPos, fileName.length()) == ".mod"))
		{
			std::string folderName = fileName.substr(0, lastPeriodPos);
			if (Utils::doesFolderExist(theConfiguration.getVic2Path() + "/mod/" + folderName))
			{
				LOG(LogLevel::Debug) << "Found mod with name " << folderName;
			}
		}
	}

	for (auto expectedMod: theConfiguration.getVic2Mods())
	{
		LOG(LogLevel::Debug) << "Expecting a mod with name " << expectedMod;
		if (!Utils::doesFolderExist(theConfiguration.getVic2Path() + "/mod/" + expectedMod))
		{
			LOG(LogLevel::Error) << "Could not find expected mod";
			exit(-1);
		}
	}
}


void setOutputName(const std::string& V2SaveFileName, Configuration& theConfiguration)
{
	std::string outputName = V2SaveFileName;

	if (outputName.empty())
	{
		return;
	}

	const int lastBackslash = V2SaveFileName.find_last_of('\\');
	const int lastSlash = V2SaveFileName.find_last_of('/');
	if ((lastBackslash == std::string::npos) && (lastSlash != std::string::npos))
	{
		outputName = outputName.substr(lastSlash + 1, outputName.length());
	}
	else if ((lastBackslash != std::string::npos) && (lastSlash == std::string::npos))
	{
		outputName = outputName.substr(lastBackslash + 1, outputName.length());
	}
	else if ((lastBackslash != std::string::npos) && (lastSlash != std::string::npos))
	{
		const int slash = std::max(lastBackslash, lastSlash);
		outputName = outputName.substr(slash + 1, outputName.length());
	}
	else if ((lastBackslash == std::string::npos) && (lastSlash == std::string::npos))
	{
		// no change, but explicitly considered
	}

	const int length = outputName.find_last_of('.');
	if ((length == std::string::npos) || (".v2" != outputName.substr(length, outputName.length())))
	{
		std::invalid_argument theException(
			 "The save was not a Vic2 save. Choose a save ending in '.v2' and convert again.");
		throw theException;
	}
	outputName = outputName.substr(0, length);

	std::replace(outputName.begin(), outputName.end(), '-', '_');
	std::replace(outputName.begin(), outputName.end(), ' ', '_');

	theConfiguration.setOutputName(outputName);
	LOG(LogLevel::Info) << "Using output name " << outputName;
}