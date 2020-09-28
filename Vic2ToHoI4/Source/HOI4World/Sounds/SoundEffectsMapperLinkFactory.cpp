#include "SoundEffectsMapperLinkFactory.h"
#include "ParserHelpers.h"



HoI4::SoundEffectsMapperLink::Factory::Factory()
{
	registerKeyword("culture", [this](const std::string& unused, std::istream& theStream) {
		soundEffectMapperLink->cultures.insert(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("sound", [this](const std::string& unused, std::istream& theStream) {
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