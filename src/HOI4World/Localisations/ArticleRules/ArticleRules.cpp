#include "ArticleRules.h"



std::string HoI4::ArticleRules::updateArticles(const std::string& language, const std::string& originalText) const
{
	if (!rules.contains(language))
	{
		return originalText;
	}

	for (const auto& rule: rules.at(language))
	{
		if (rule.doesRuleApply(originalText))
		{
			return rule.applyRuleToText(originalText);
		}
	}

	return originalText;
}