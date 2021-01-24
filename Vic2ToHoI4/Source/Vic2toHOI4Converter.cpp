#include "Configuration.h"
#include "HOI4World/HoI4World.h"
#include "Log.h"
#include "Mappers/Provinces/ProvinceMapper.h"
#include "OSCompatibilityLayer.h"
#include "OutHoi4/OutMod.h"
#include "V2World/World/World.h"
#include "V2World/World/WorldFactory.h"
#include <stdexcept>



void checkMods(const Configuration& theConfiguration);
void ConvertV2ToHoI4()
{
	const auto theConfiguration = Configuration::Factory{}.importConfiguration("configuration.txt");
	checkMods(*theConfiguration);
	clearOutputFolder(theConfiguration->getOutputName());

	const auto provinceMapper = Mappers::ProvinceMapper::Parser{}.initializeMapper(*theConfiguration);

	const auto sourceWorld = Vic2::World::Factory{*theConfiguration}.importWorld(*theConfiguration, provinceMapper);
	const HoI4::World destWorld(*sourceWorld, provinceMapper, *theConfiguration);

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

	for (const auto& modFolder: commonItems::GetAllSubfolders(theConfiguration.getVic2Path() + "/mod"))
	{
		Log(LogLevel::Info) << "\tFound mod folder with path " << modFolder;
	}

	for (const auto& expectedMod: theConfiguration.getVic2Mods())
	{
		Log(LogLevel::Info) << "\tExpecting a mod with name \"" << expectedMod.getName() << "\" and path "
								  << expectedMod.getDirectory();
		if (!commonItems::DoesFolderExist(theConfiguration.getVic2Path() + "/mod/" + expectedMod.getDirectory()))
		{
			throw std::runtime_error("Could not find expected mod folder " + expectedMod.getDirectory());
		}
	}
}