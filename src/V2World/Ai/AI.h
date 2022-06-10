#ifndef AI_H
#define AI_H



#include "src/V2World/Ai/AIStrategy.h"
#include "src/V2World/Provinces/Province.h"



namespace Vic2
{

struct StrategyData
{
	int value;
	std::vector<int> provinces;
};

class AI
{
  public:
	class Factory;

	[[nodiscard]] const auto& getStrategies() const { return aiStrategies; }
	[[nodiscard]] const auto& getConquerStrategies() const { return conquerStrategies; }
	[[nodiscard]] const auto& getConsolidatedStrategies() const { return consolidatedConquerStrategies; }

	void consolidateConquerStrategies(const std::map<int, std::shared_ptr<Province>>& provinces);

  private:
	std::vector<AIStrategy> aiStrategies;
	std::vector<AIStrategy> conquerStrategies;
	std::map<std::string, StrategyData> consolidatedConquerStrategies;
};

bool operator==(const StrategyData& one, const StrategyData& other);

} // namespace Vic2



#endif // AI_H