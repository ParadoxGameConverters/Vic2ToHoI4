#include "OccupationLawFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::OccupationLaw::Factory::Factory()
{
	registerKeyword("icon", [this](std::istream& theStream) {
		occupationLaw->setIcon(commonItems::singleInt(theStream).getInt());
	});
	registerKeyword("default_law", [this](const std::string& unused, std::istream& theStream) {
		occupationLaw->setDefaultLaw(true);
		commonItems::ignoreItem(unused, theStream);
	});
	registerKeyword("sound_effect", [this](std::istream& theStream) {
		occupationLaw->setSoundEffect(commonItems::singleString(theStream).getString());
	});
	registerKeyword("visible", [this](std::istream& theStream) {
		occupationLaw->setVisible(commonItems::stringOfItem(theStream).getString());
	});
	registerKeyword("state_modifier", [this](std::istream& theStream) {
		occupationLaw->setStateModifier(commonItems::stringOfItem(theStream).getString());
	});
	registerKeyword("suppressed_state_modifier", [this](std::istream& theStream) {
		occupationLaw->setSuppressedStateModifier(commonItems::stringOfItem(theStream).getString());
	});
	registerKeyword("starting_law", [this](const std::string& unused, std::istream& theStream) {
		occupationLaw->setStartingLaw(true);
		commonItems::ignoreItem(unused, theStream);
	});
	registerKeyword("ai_will_do", [this](std::istream& theStream) {
		occupationLaw->setAiWillDo(commonItems::stringOfItem(theStream).getString());
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<HoI4::OccupationLaw> HoI4::OccupationLaw::Factory::getOccupationLaw(const std::string& name,
	 std::istream& theStream)
{
	occupationLaw = std::make_unique<OccupationLaw>();
	occupationLaw->setName(name);

	parseStream(theStream);

	return std::move(occupationLaw);
}