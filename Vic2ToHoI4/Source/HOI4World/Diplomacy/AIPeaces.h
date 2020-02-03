#ifndef HOI4_AI_PEACES
#define HOI4_AI_PEACES



#include "AIPeace.h"
#include "newParser.h"
#include <set>
#include <string>
#include <vector>



namespace HoI4
{

class AIPeaces: commonItems::parser
{
	public:
		AIPeaces() noexcept;

		void updateAIPeaces(const std::set<std::string>& majorIdeologies);

		void output(std::set<std::string> majorIdeologies);

	private:
		std::vector<AIPeace> thePeaces;
};

}



#endif // HOI4_AI_PEACES
