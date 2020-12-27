#ifndef VIC2_AI_STRATEGY_H
#define VIC2_AI_STRATEGY_H



#include <string>



namespace Vic2
{

class AIStrategy
{
  public:
	class Factory;

	[[nodiscard]] const auto& getType() const { return type; }
	[[nodiscard]] const auto& getID() const { return id; }
	[[nodiscard]] int getProvID() const { return provID; }
	[[nodiscard]] int getValue() const { return value; }

  private:
	std::string type;
	std::string id;
	int provID = 0;
	int value = 0;
};

} // namespace Vic2



#endif // VIC2_AI_STRATEGY_H