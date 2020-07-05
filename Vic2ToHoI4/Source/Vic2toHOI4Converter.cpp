#include "Configuration.h"
#include "HOI4World/HoI4World.h"
#include "Log.h"
#include "Mappers/Provinces/ProvinceMapper.h"
#include "OSCompatibilityLayer.h"
#include "OutHoi4/OutMod.h"
#include "V2World/Vic2Localisations.h"
#include "V2World/World.h"
#include <stdexcept>



void checkMods(const Configuration& theConfiguration);
void ConvertV2ToHoI4()
{
	const auto theConfiguration = Configuration::Factory{}.importConfiguration("configuration.txt");
	checkMods(*theConfiguration);
	clearOutputFolder(theConfiguration->getOutputName());

	const auto provinceMapper = mappers::ProvinceMapper::Parser{}.initializeMapper(*theConfiguration);

	Vic2::World sourceWorld(provinceMapper, *theConfiguration);
	const HoI4::World destWorld(&sourceWorld, provinceMapper, *theConfiguration);

	output(destWorld,
		 theConfiguration->getOutputName(),
		 theConfiguration->getDebug(),
		 theConfiguration->getVic2Mods(),
		 theConfiguration->getVic2ModPath(),
		 *theConfiguration);
	Log(LogLevel::Progress) << "100%";
	Log(LogLevel::Info) << "* Conversion complete *";
}


void checkMods(const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "Double-checking Vic2 mods";

	for (const auto& modFolder: Utils::GetAllSubfolders(theConfiguration.getVic2Path() + "/mod"))
	{
		Log(LogLevel::Info) << "\tFound mod with folder name " << modFolder;
	}

	for (const auto& expectedMod: theConfiguration.getVic2Mods())
	{
		Log(LogLevel::Info) << "\tExpecting a mod with folder name " << expectedMod;
		if (!Utils::DoesFolderExist(theConfiguration.getVic2Path() + "/mod/" + expectedMod))
		{
			throw std::runtime_error("Could not find expected mod folder " + expectedMod);
		}
	}
}