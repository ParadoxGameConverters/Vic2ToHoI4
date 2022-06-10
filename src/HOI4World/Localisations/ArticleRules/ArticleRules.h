#ifndef ARTICLE_RULES_H
#define ARTICLE_RULES_H



#include "src/HOI4World/Localisations/ArticleRules/ArticleRule.h"
#include <map>
#include <string>
#include <vector>



namespace HoI4
{

class ArticleRules
{
  public:
	class Builder;
	class Factory;

	[[nodiscard]] std::string updateArticles(const std::string& language, const std::string& originalText) const;

  private:
	std::map<std::string, std::vector<ArticleRule>> rules;
};

} // namespace HoI4



#endif // ARTICLE_RULES_H