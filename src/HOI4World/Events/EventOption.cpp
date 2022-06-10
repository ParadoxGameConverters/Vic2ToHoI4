#include "src/HOI4World/Events/EventOption.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::EventOption::EventOption(std::istream& theStream)
{
	registerKeyword("name", [this](std::istream& theStream) {
		const commonItems::singleString nameString(theStream);
		name = nameString.getString();
	});
	registerKeyword("ai_chance", [this](std::istream& theStream) {
		const commonItems::stringOfItem chanceString(theStream);
		aiChance = chanceString.getString();
	});
	registerKeyword("hidden_effect", [this](std::istream& theStream) {
		const commonItems::stringOfItem effectString(theStream);
		hiddenEffect = effectString.getString();
	});
	registerRegex(commonItems::catchallRegex, [this](const std::string& blockName, std::istream& theStream) {
		const commonItems::stringOfItem scriptBlockString(theStream);
		const auto blockString = blockName + " " + scriptBlockString.getString() + "\n";
		scriptBlocks.push_back(blockString);
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}