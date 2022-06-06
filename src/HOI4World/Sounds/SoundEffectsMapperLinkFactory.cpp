#include "SoundEffectsMapperLinkFactory.h"
#include "external/common_items/ParserHelpers.h"



HoI4::SoundEffectsMapperLink::Factory::Factory()
{
	registerKeyword("culture", [this](std::istream& theStream) {
		soundEffectMapperLink->cultures.insert(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("sound", [this](std::istream& theStream) {
		soundEffectMapperLink->sounds.insert(commonItems::singleString{theStream}.getString());
	});
}


std::unique_ptr<HoI4::SoundEffectsMapperLink> HoI4::SoundEffectsMapperLink::Factory::getSoundEffectMapperLink(
	 std::istream& theStream)
{
	soundEffectMapperLink = std::make_unique<SoundEffectsMapperLink>();
	parseStream(theStream);
	return std::move(soundEffectMapperLink);
}