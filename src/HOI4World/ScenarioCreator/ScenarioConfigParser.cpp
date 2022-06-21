#include "src/HOI4World/ScenarioCreator/ScenarioConfigParser.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"

HoI4::ConfigParser::ConfigParser(std::string filename, bool preGenned)
{
	if (!preGenned)
	{
		registerKeys();
	}
	else
	{
		registerKeysPreGenned();
	}
		parseFile(filename);
		clearRegisteredKeywords();
}

void HoI4::ConfigParser::registerKeys()
{
	registerKeyword("valid", [this](std::istream& the_stream) {
		const auto& vector_roles = commonItems::getStrings(the_stream);
		possible_roles_ = std::set<std::string>(vector_roles.begin(), vector_roles.end());
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}

void HoI4::ConfigParser::registerKeysPreGenned()
{
	registerRegex(R"(\w+)", [this](const std::string& tag, std::istream& the_stream) {
		const auto& role_name = commonItems::getString(the_stream);
		possible_roles_.emplace(role_name);
		role_assignments_.emplace(tag, role_name);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}
