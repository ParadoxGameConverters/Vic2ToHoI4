#ifndef AI_H
#define AI_H



#include "AIStrategy.h"
#include "V2World/Provinces/Province.h"



namespace Vic2
{

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
	std::map<std::string, std::pair<int, std::vector<int>>> consolidatedConquerStrategies; // tag -> value, provinces
};

} // namespace Vic2



#endif // AI_H