#ifndef ARTICLE_RULES_DEFINITION_H
#define ARTICLE_RULES_DEFINITION_H



#include "external/common_items/ConvenientParser.h"
#include <string>
#include <vector>



namespace HoI4
{

class ArticleRulesDefinition: commonItems::parser
{
  public:
	ArticleRulesDefinition(std::istream& theStream);

	[[nodiscard]] const auto& getLanguage() const { return language; }
	[[nodiscard]] const auto& getMatchers() const { return matchers; }
	[[nodiscard]] const auto& getReplacement() const { return replacement; }

  private:
	std::string language;
	std::vector<std::string> matchers;
	std::string replacement;
};

} // namespace HoI4



#endif // ARTICLE_RULES_DEFINITION_H