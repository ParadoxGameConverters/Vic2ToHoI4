#include "src/HOI4World/Localisations/GrammarMappings.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::GrammarMappings::GrammarMappings()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& category, std::istream& theStream) {
		grammarMappings.emplace(category, commonItems::singleString{theStream}.getString());
	});
}


std::map<std::string, std::string> HoI4::GrammarMappings::importGrammarMappings()
{
	grammarMappings.clear();
	parseFile(std::filesystem::path("Configurables/grammar.txt"));
	return grammarMappings;
}