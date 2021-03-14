#ifndef MERGE_RULE_H
#define MERGE_RULE_H



#include "Parser.h"
#include <string>
#include <vector>



namespace Mappers
{
class MergeRule: commonItems::parser
{
  public:
	explicit MergeRule(std::istream& theStream);

	bool isEnabled() const { return enabled; }
	std::string getMaster() const { return master; }
	std::vector<std::string> getSlaves() const { return slaves; }

  private:
	bool enabled = false;
	std::string master = "";
	std::vector<std::string> slaves;
};
} // namespace Mappers



#endif // MERGE_RULE_H