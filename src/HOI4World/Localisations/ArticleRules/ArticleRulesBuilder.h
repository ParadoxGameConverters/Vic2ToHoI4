#ifndef ARTICLE_RULES_BUILDER_H
#define ARTICLE_RULES_BUILDER_H



#include "src/HOI4World/Localisations/ArticleRules/ArticleRules.h"
#include <memory>



namespace HoI4
{

class ArticleRules::Builder
{
  public:
	Builder() { rules = std::make_unique<ArticleRules>(); }
	std::unique_ptr<ArticleRules> build() { return std::move(rules); }

	Builder& addRules(std::string language, std::vector<ArticleRule> rulesForLanguage)
	{
		rules->rules[std::move(language)] = std::move(rulesForLanguage);
		return *this;
	}

  private:
	std::unique_ptr<ArticleRules> rules;
};

} // namespace HoI4



#endif // ARTICLE_RULES_BUILDER_H