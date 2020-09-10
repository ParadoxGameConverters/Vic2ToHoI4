#ifndef VIC2_VIC2AI_H_
#define VIC2_VIC2AI_H_



#include "Parser.h"



namespace Vic2
{

class AIStrategy;


class Vic2AI: commonItems::parser
{
  public:
	explicit Vic2AI(std::istream& theStream);

	const auto& getStrategies() const { return aiStrategies; }

  private:
	std::vector<AIStrategy> aiStrategies;
};

} // namespace Vic2



#endif // VIC2_VIC2AI_H_