#ifndef HoI4AISTRATEGY_H_
#define HoI4AISTRATEGY_H_



#include "HOI4World/States/HoI4States.h"
#include "Mappers/Provinces/ProvinceMapper.h"
#include "V2World/Ai/AIStrategy.h"
#include <vector>



namespace HoI4
{

class AIStrategy
{
  public:
	explicit AIStrategy(const std::string& strategyType,
		 const std::string& HoI4Tag,
		 const std::pair<int, std::vector<int>>& vic2StrategyData,
		 const States& states,
		 const Mappers::ProvinceMapper& provinceMapper);
	AIStrategy(const Vic2::AIStrategy& oldStrategy, const std::string& HoI4Tag);

	void determineClaimedState(const std::pair<int, std::vector<int>>& vic2StrategyData,
		 const States& states,
		 const Mappers::ProvinceMapper& provinceMapper);

	[[nodiscard]] const auto& getType() const { return type; }
	[[nodiscard]] const auto& getID() const { return id; }
	[[nodiscard]] int getValue() const { return value; }
	[[nodiscard]] const auto& getClaimedState() const { return claimedState; }

  private:
	std::string type;
	std::string id;
	int value = 0;
	std::optional<int> claimedState;
};

} // namespace HoI4



#endif // HoI4AISTRATEGY_H_