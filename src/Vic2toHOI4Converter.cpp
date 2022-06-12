#include "external/common_items/ConverterVersion.h"
#include "external/common_items/Log.h"
#include "external/common_items/ModLoader/ModFilesystem.h"
#include "src/Configuration.h"
#include "src/HOI4World/HoI4World.h"
#include "src/Mappers/Provinces/ProvinceMapper.h"
#include "src/Mappers/Provinces/ProvinceMapperFactory.h"
#include "src/OutHoi4/OutMod.h"
#include "src/V2World/World/World.h"
#include "src/V2World/World/WorldFactory.h"



void ConvertV2ToHoI4(const commonItems::ConverterVersion& converterVersion)
{
	const auto the_configuration = Configuration::Factory().importConfiguration("configuration.txt", converterVersion);
	clearOutputFolder(the_configuration->getOutputName());

	const auto provinceMapper =
		 Mappers::ProvinceMapper::Factory(*the_configuration).importProvinceMapper(*the_configuration);

	const commonItems::ModFilesystem filesystem(the_configuration->getVic2Path(), the_configuration->getVic2Mods());
	const auto sourceWorld =
		 Vic2::World::Factory(*the_configuration, filesystem).importWorld(*the_configuration, *provinceMapper);
	const HoI4::World destWorld(*sourceWorld, *provinceMapper, *the_configuration);

	output(destWorld,
		 the_configuration->getOutputName(),
		 the_configuration->getDebug(),
		 the_configuration->getVic2Mods(),
		 *the_configuration);
	Log(LogLevel::Progress) << "100%";
	Log(LogLevel::Notice) << "* Conversion complete *";
}
