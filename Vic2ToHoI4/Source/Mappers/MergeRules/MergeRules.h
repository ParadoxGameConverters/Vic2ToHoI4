#ifndef MERGE_RULES
#define MERGE_RULES



#include <map>
#include <string>
#include <vector>


namespace Mappers
{

class MergeRules
{
  public:
	class Factory;

	[[nodiscard]] std::map<std::string, std::vector<std::string>> getRules() const { return rules; }

  private:
	std::map<std::string, std::vector<std::string>> rules;
};

} // namespace Mappers



#endif // MERGE_RULES