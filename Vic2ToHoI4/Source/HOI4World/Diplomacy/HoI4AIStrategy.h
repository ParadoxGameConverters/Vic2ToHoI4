#ifndef HoI4AISTRATEGY_H_
#define HoI4AISTRATEGY_H_



#include "V2World/Ai/AIStrategy.h"



namespace HoI4
{

class AIStrategy
{
  public:
	explicit AIStrategy(const std::string& strategyType, const std::string& HoI4Tag, int strategyValue):
		 type(strategyType), id(HoI4Tag), value(strategyValue)
	{
	}

	AIStrategy(const Vic2::AIStrategy& oldStrategy, const std::string& HoI4Tag):
		 type(oldStrategy.getType()), id(HoI4Tag), value(oldStrategy.getValue())
	{
		if (oldStrategy.getType() == "befriend")
		{
			type = "alliance";
			value = value / 2;
		}
		if (oldStrategy.getType() == "threat")
		{
			type = "contain";
		}
		if (oldStrategy.getType() == "rival")
		{
			type = "declare_war";
		}
	}

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