#include "src/HOI4World/Sounds/SoundEffectsMapperFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/Sounds/SoundEffectsMapperLink.h"
#include "src/HOI4World/Sounds/SoundEffectsMapping.h"



HoI4::SoundEffectsMapper::Factory::Factory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& name, std::istream& theStream) {
		const auto soundEffectMapping = soundEffectMappingFactory.getSoundEffectMapping(theStream);
		for (const auto& link: soundEffectMapping->getLinks())
		{
			for (const auto& culture: link.getCultures())
			{
				if (auto soundEffectsMapping = mapper->mappings.find(culture);
					 soundEffectsMapping != mapper->mappings.end())
				{
					soundEffectsMapping->second.insert(SoundEffectsMapping(name, link.getSounds()));
				}
				else
				{
					mapper->mappings[culture] = std::set<SoundEffectsMapping>{SoundEffectsMapping(name, link.getSounds())};
				}
			}
		}
	});
}


std::unique_ptr<HoI4::SoundEffectsMapper> HoI4::SoundEffectsMapper::Factory::getMapper()
{
	mapper = std::make_unique<SoundEffectsMapper>();
	parseFile(std::filesystem::path("Configurables/Sounds/CultureToVoiceMappings.txt"));
	return std::move(mapper);
}