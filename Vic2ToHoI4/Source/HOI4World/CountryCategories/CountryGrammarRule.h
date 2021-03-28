#ifndef COUNTRY_GRAMMAR_RULE_H
#define COUNTRY_GRAMMAR_RULE_H



#include <optional>
#include <string>



namespace HoI4
{

struct CountryGrammarRule
{
	std::string category;
	std::string tag;
	std::optional<std::string> extra;

	bool operator==(const CountryGrammarRule& rhs) const
	{
		return category == rhs.category && tag == rhs.tag &&
				 ((!extra && !rhs.extra) || (extra && rhs.extra && *extra == *rhs.extra));
	}
};

} // namespace HoI4



#endif // COUNTRY_GRAMMAR_RULE_H