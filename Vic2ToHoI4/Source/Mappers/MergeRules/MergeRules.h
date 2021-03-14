#ifndef MERGE_RULES
#define MERGE_RULES



#include "Parser.h"
#include <map>
#include <string>
#include <vector>
#include "MergeRuleFactory.h"



class MergeRules: commonItems::parser
{
	public:
		MergeRules() noexcept;

		std::map<std::string, std::vector<std::string>> getRules() const { return rules; }

	private:
		Mappers::MergeRule::Factory mergeRuleFactory;
		std::map<std::string, std::vector<std::string>> rules;
};



#endif // MERGE_RULES
