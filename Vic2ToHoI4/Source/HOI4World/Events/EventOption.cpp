#include "EventOption.h"
#include "ParserHelpers.h"



HoI4::EventOption::EventOption(std::istream& theStream)
{
	registerKeyword("name", [this](const std::string& unused, std::istream& theStream){
		const commonItems::singleString nameString(theStream);
		name = nameString.getString();
	});
	registerKeyword("ai_chance", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfItem chanceString(theStream);
		aiChance = chanceString.getString();
	});
	registerKeyword("hidden_effect", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfItem effectString(theStream);
		hiddenEffect = effectString.getString();
	});
	registerRegex("[a-zA-Z0-9_\\.]+", [this](const std::string& blockName, std::istream& theStream) {
		const commonItems::stringOfItem scriptBlockString(theStream);
		const auto blockString = blockName + " " + scriptBlockString.getString() + "\n";
		scriptBlocks.push_back(blockString);
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}