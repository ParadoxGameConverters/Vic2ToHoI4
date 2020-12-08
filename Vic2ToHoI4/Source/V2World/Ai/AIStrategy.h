#ifndef VIC2_AI_STRATEGY_H_
#define VIC2_AI_STRATEGY_H_



#include "Parser.h"



namespace Vic2
{

class AIStrategy: commonItems::parser
{
  public:
	explicit AIStrategy(const std::string& strategyType, std::istream& theStream);

	const auto& getType() const { return type; }
	const auto& getID() const { return id; }
	int getProvID() const { return provID; }
	int getValue() const { return value; }

  private:
	std::string type;
	std::string id;
	int provID = 0;
	int value = 0;
};

} // namespace Vic2



#endif // VIC2_AISTRATEGY_H_