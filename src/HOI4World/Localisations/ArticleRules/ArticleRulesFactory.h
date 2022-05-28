#ifndef ARTICLE_RULES_FACTORY_H
#define ARTICLE_RULES_FACTORY_H



#include "ArticleRules.h"
#include "Parser.h"
#include <memory>
#include <string>



namespace HoI4
{

class ArticleRules::Factory: commonItems::parser
{
  public:
	Factory();
	[[nodiscard]] std::unique_ptr<ArticleRules> getRules(const std::string& rulesFile);

  private:
	std::unique_ptr<ArticleRules> rules;
};

} // namespace HoI4



#endif // ARTICLE_RULES_FACTORY_H