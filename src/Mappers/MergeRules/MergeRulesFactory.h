#ifndef MERGE_RULES_FACTORY_H
#define MERGE_RULES_FACTORY_H



#include "MergeRuleFactory.h"
#include "MergeRules.h"
#include "Parser.h"
#include <memory>



namespace Mappers
{

class MergeRules::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<MergeRules> importMergeRules();

  private:
	MergeRule::Factory mergeRuleFactory;
	std::unique_ptr<MergeRules> mergeRules;
};

} // namespace Mappers



#endif // MERGE_RULES_FACTORY_H