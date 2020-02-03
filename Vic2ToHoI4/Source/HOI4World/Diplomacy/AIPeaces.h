#ifndef AI_PEACES_H
#define AI_PEACES_H



#include "AIPeace.h"
#include "newParser.h"
#include <string>
#include <vector>



namespace HoI4
{

class AiPeaces: commonItems::parser
{
	public:
		AiPeaces() noexcept;

		void updateAiPeace(std::string_view name, const std::string& replacementEnable);

		[[nodiscard]] const auto& getThePeaces() const { return thePeaces; }

	private:
		std::vector<AiPeace> thePeaces;
};

}



#endif // AI_PEACES_H
