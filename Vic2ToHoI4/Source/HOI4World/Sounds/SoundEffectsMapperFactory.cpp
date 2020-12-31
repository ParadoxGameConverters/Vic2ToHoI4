#include "SoundEffectsMapperFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"
#include "SoundEffectsMapperLink.h"
#include "SoundEffectsMapping.h"



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
	parseFile("DataFiles/Sounds/CultureToVoiceMappings.txt");
	return std::move(mapper);
}