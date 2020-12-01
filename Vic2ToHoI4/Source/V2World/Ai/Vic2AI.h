#ifndef VIC2_VIC2AI_H_
#define VIC2_VIC2AI_H_



#include "AIStrategy.h"
#include "Parser.h"
#include "V2World/Provinces/Province.h"

namespace Vic2
{

class Vic2AI: commonItems::parser
{
  public:
	explicit Vic2AI(std::istream& theStream);

	[[nodiscard]] const auto& getStrategies() const { return aiStrategies; }
	[[nodiscard]] const auto& getConquerStrategies() const { return conquerStrategies; }
	[[nodiscard]] const auto& getConsolidatedStrategies() const { return consolidatedConquerStrategies; }
	void consolidateConquerStrategies(const std::map<int, std::shared_ptr<Province>>& provinces);

  private:
	void updateStrategy(const std::string& tag, int valueToAdd);

	std::vector<AIStrategy> aiStrategies;
	std::vector<AIStrategy> conquerStrategies;
	std::map<std::string, int> consolidatedConquerStrategies;
};

} // namespace Vic2



#endif // VIC2_VIC2AI_H_