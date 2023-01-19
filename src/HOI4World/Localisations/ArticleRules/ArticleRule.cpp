#include "src/HOI4World/Localisations/ArticleRules/ArticleRule.h"



bool HoI4::ArticleRule::doesRuleApply(const std::string& text) const
{
	std::smatch match;
	return std::regex_match(text, match, matcher);
}


std::string HoI4::ArticleRule::applyRuleToText(const std::string& originalText) const
{
	return std::regex_replace(originalText, matcher, replacement);
}