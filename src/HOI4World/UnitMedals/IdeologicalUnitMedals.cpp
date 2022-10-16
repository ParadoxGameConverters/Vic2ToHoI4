#include "src/HOI4World/UnitMedals/IdeologicalUnitMedals.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Parser.h"
#include "external/common_items/ParserHelpers.h"



std::map<std::string, std::string> HoI4::ImportIdeologicalUnitMedals()
{
	std::map<std::string, std::string> ideologies_to_unit_medals;

	commonItems::parser cost_modifiers_parser;

	cost_modifiers_parser.registerRegex(commonItems::catchallRegex,
		[&ideologies_to_unit_medals](const std::string& ideology, std::istream& the_stream) {
		// need to trim the outer wrapper off things
		const auto raw_string = commonItems::stringOfItem(the_stream).getString();
		ideologies_to_unit_medals.emplace(ideology, raw_string.substr(4, raw_string.size() - 6));
	});

	cost_modifiers_parser.parseFile("Configurables/ideological_unit_medals.txt");

	return ideologies_to_unit_medals;
}