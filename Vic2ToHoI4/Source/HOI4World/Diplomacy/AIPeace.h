#ifndef HOI4_AI_PEACE
#define HOI4_AI_PEACE



#include "newParser.h"
#include <string>



namespace HoI4
{

class AIPeace: commonItems::parser
{
	public:
		AIPeace(const std::string& theName, std::istream& theStream);

		std::string getName() const { return name; }

		void replaceEnable(const std::string& newEnable) { enable = newEnable; }

		friend std::ostream& operator<<(std::ostream& outStream, const HoI4::AIPeace& outPeace);

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

std::ostream& operator<<(std::ostream& outStream, const HoI4::AIPeace& outPeace);

}



#endif // HOI4_AI_PEACES
