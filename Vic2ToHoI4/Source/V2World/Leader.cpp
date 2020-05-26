#include "Leader.h"
#include "ParserHelpers.h"



Vic2::Leader::Leader(std::istream& theStream)
{
	registerKeyword("name", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString nameString(theStream);
		name = nameString.getString();
		if (name[0] == '\"')
		{
			name = name.substr(1, name.length() - 2);
		}
	});
	registerKeyword("type", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString typeString(theStream);
		type = typeString.getString();
		if (type[0] == '\"')
		{
			type = type.substr(1, type.length() - 2);
		}
	});
	registerKeyword("personality", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString personalityString(theStream);
		personality = personalityString.getString();
		if (personality[0] == '\"')
		{
			personality = personality.substr(1, personality.length() - 2);
		}
	});
	registerKeyword("background", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString backgroundString(theStream);
		background = backgroundString.getString();
		if (background[0] == '\"')
		{
			background = background.substr(1, background.length() - 2);
		}
	});
	registerKeyword("prestige", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleDouble prestigeString(theStream);
		prestige = prestigeString.getDouble();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}