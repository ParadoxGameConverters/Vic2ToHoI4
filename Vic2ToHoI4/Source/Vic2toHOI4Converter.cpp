#include "Configuration.h"
#include "ConverterVersion.h"
#include "HOI4World/HoI4World.h"
#include "Log.h"
#include "Mappers/Provinces/ProvinceMapper.h"
#include "Mappers/Provinces/ProvinceMapperFactory.h"
#include "OutHoi4/OutMod.h"
#include "V2World/World/World.h"
#include "V2World/World/WorldFactory.h"

void ConvertV2ToHoI4(const commonItems::ConverterVersion& converterVersion)
{
	const auto theConfiguration = Configuration::Factory().importConfiguration("configuration.txt", converterVersion);
	clearOutputFolder(theConfiguration->getOutputName());

	const auto provinceMapper =
		 Mappers::ProvinceMapper::Factory(*theConfiguration).importProvinceMapper(*theConfiguration);

	const auto sourceWorld = Vic2::World::Factory(*theConfiguration).importWorld(*theConfiguration, *provinceMapper);
	const HoI4::World destWorld(*sourceWorld, *provinceMapper, *theConfiguration);

	output(destWorld,
		 theConfiguration->getOutputName(),
		 theConfiguration->getDebug(),
		 theConfiguration->getVic2Mods(),
		 *theConfiguration);
	Log(LogLevel::Progress) << "100%";
	Log(LogLevel::Info) << "* Conversion complete *";
}
