#include "EventOption.h"
#include "ParserHelpers.h"



HoI4::EventOption::EventOption(std::istream& theStream)
{
	registerKeyword("name", [this](const std::string& unused, std::istream& theStream){
		commonItems::singleString nameString(theStream);
		name = nameString.getString();
	});
	registerKeyword("ai_chance", [this](const std::string& unused, std::istream& theStream) {
		commonItems::stringOfItem chanceString(theStream);
		aiChance = chanceString.getString();
	});
	registerKeyword(std::regex("[a-zA-Z0-9_\\.]+"), [this](const std::string& blockName, std::istream& theStream) {
		commonItems::stringOfItem scriptBlockString(theStream);
		std::string blockString = blockName + " " + scriptBlockString.getString() + "\n";
		scriptBlocks.push_back(blockString);
	});
	registerKeyword("hidden_effect", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString effectString(theStream);
		hiddenEffect = effectString.getString();
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}