#ifndef ARTICLE_RULE_H
#define ARTICLE_RULE_H



#include <regex>
#include <string>



namespace HoI4
{

class ArticleRule
{
  public:
	class Builder;
	[[nodiscard]] bool doesRuleApply(const std::string& text) const;
	[[nodiscard]] std::string applyRuleToText(const std::string& originalText) const;

  private:
	std::regex matcher;
	std::string replacement;
};

} // namespace HoI4



#endif // ARTICLE_RULE_H