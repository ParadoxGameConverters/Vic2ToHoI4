#include "src/HOI4World/Sounds/SoundEffectMappingFactory.h"



HoI4::SoundEffectMapping::Factory::Factory()
{
	registerKeyword("link", [this](std::istream& theStream) {
		soundEffectMapping->links.push_back(*soundEffectsMapperLinkFactory.getSoundEffectMapperLink(theStream));
	});
}


std::unique_ptr<HoI4::SoundEffectMapping> HoI4::SoundEffectMapping::Factory::getSoundEffectMapping(
	 std::istream& theStream)
{
	soundEffectMapping = std::make_unique<SoundEffectMapping>();
	parseStream(theStream);
	return std::move(soundEffectMapping);
}