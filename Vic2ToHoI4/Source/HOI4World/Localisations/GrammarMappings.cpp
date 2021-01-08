#include "GrammarMappings.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::GrammarMappings::GrammarMappings()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& category, std::istream& theStream) {
		grammarMappings.insert(std::make_pair(category, commonItems::singleString{theStream}.getString()));
	});
}


std::map<std::string, std::string> HoI4::GrammarMappings::importGrammarMappings()
{
	grammarMappings.clear();
	parseFile("Configurables/grammar.txt");
	return grammarMappings;
}