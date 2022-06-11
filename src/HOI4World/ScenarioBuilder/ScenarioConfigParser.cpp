#include "src/HOI4World/ScenarioBuilder/ScenarioConfigParser.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"

HoI4::ConfigParser::ConfigParser(std::string filename, bool preGenned)
{
	if (!preGenned)
	{
		registerKeys();
		parseFile(filename);
		clearRegisteredKeywords();
	}
	else
	{
		registerKeysPreGenned();
		parseFile(filename);
		clearRegisteredKeywords();
	}
}

void HoI4::ConfigParser::registerKeys()
{
	registerKeyword("valid", [this](std::istream& theStream) {
		const auto& vectorRoles = commonItems::getStrings(theStream);
		possibleRoles = std::set<std::string>(vectorRoles.begin(), vectorRoles.end());
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}

void HoI4::ConfigParser::registerKeysPreGenned()
{
	registerRegex(R"(\w+)", [this](const std::string& tag, std::istream& theStream) {
		const auto& roleName = commonItems::getString(theStream);
		possibleRoles.emplace(roleName);
		roleAssignments.emplace(tag, roleName);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}
