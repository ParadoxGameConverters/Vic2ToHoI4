#ifndef AI_PEACE_H
#define AI_PEACE_H



#include "Parser.h"
#include <string>



namespace HoI4
{

class AiPeace: commonItems::parser
{
  public:
	AiPeace(const std::string& theName, std::istream& theStream);

	[[nodiscard]] std::string_view getName() const { return name; }

	void replaceEnable(const std::string& newEnable) { enable = newEnable; }

	friend std::ostream& operator<<(std::ostream& outStream, const AiPeace& outPeace);

  private:
	std::string name;

	std::string enable;

	int annexRandomness = 0;
	int liberateRandomness = 0;
	int puppetRandomness = 0;
	int takeStatesRandomness = 0;
	int forceGovernmentRandomness = 0;

	std::string annex;
	std::string liberate;
	std::string puppet;
	std::string takeStates;
	std::string forceGovernment;
};

} // namespace HoI4



#endif // AI_PEACE_H