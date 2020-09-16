#ifndef HoI4AISTRATEGY_H_
#define HoI4AISTRATEGY_H_



#include "../../V2World/Ai/AIStrategy.h"



namespace HoI4
{

class AIStrategy
{
  public:
	explicit AIStrategy(std::string strategyType): type(std::move(strategyType)) {}

	AIStrategy(const Vic2::AIStrategy& oldStrategy):
		 type(std::move(oldStrategy.getType())), id(oldStrategy.getID()), value(oldStrategy.getValue())
	{
	}

	void setID(const std::string HoI4Tag) { id = HoI4Tag; }
	void setValue(const int strategyValue) { value = strategyValue; }
	void updateStrategy();

	[[nodiscard]] const auto& getType() const { return type; }
	[[nodiscard]] const auto& getID() const { return id; }
	[[nodiscard]] int getValue() const { return value; }

  private:
	std::string type;
	std::string id;
	int value = 0;
};

} // namespace HoI4



#endif // HoI4AISTRATEGY_H_