#ifndef VIC2_VIC2AI_H_
#define VIC2_VIC2AI_H_



#include "Parser.h"



namespace Vic2
{

class Province;
class AIStrategy;


class Vic2AI: commonItems::parser
{
  public:
	explicit Vic2AI(std::istream& theStream);

	[[nodiscard]] const auto& getStrategies() const { return aiStrategies; }
	[[nodiscard]] const auto& getConquerStrategies() const { return conquerStrategies; }
	[[nodiscard]] const auto& getConsolidatedStrategies() const { return consolidatedConquerStrategies; }
	void consolidateConquerStrategies(const std::map<int, std::shared_ptr<Province>>& provinces);
	void updateStrategy(const std::string& tag, int valueToAdd);

  private:
	std::vector<AIStrategy> aiStrategies;
	std::vector<AIStrategy> conquerStrategies;
	std::map<std::string, int> consolidatedConquerStrategies;
};

} // namespace Vic2



#endif // VIC2_VIC2AI_H_