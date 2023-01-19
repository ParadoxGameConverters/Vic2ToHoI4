#ifndef GRAMMAR_MAPPINGS_H
#define GRAMMAR_MAPPINGS_H



#include "external/common_items/ConvenientParser.h"



namespace HoI4
{

class GrammarMappings: commonItems::parser
{
  public:
	GrammarMappings();

	std::map<std::string, std::string> importGrammarMappings();

  private:
	std::map<std::string, std::string> grammarMappings;
};

} // namespace HoI4



#endif // GRAMMAR_MAPPINGS_H