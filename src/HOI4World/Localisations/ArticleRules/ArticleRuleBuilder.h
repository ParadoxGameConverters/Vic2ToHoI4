#ifndef ARTICLE_RULE_BUILDER
#define ARTICLE_RULE_BUILDER



#include "src/HOI4World/Localisations/ArticleRules/ArticleRule.h"



namespace HoI4
{

class ArticleRule::Builder
{
  public:
	Builder() { rule = std::make_unique<ArticleRule>(); }
	std::unique_ptr<ArticleRule> build() { return std::move(rule); }

	Builder& setMatcher(std::regex matcher)
	{
		rule->matcher = std::move(matcher);
		return *this;
	}

	Builder& setReplacement(std::string replacement)
	{
		rule->replacement = std::move(replacement);
		return *this;
	}

  private:
	std::unique_ptr<ArticleRule> rule;
};

} // namespace HoI4



#endif // ARTICLE_RULE_BUILDER