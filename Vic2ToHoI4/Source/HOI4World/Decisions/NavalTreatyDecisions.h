#ifndef NAVAL_TREATY_DECISIONS
#define NAVAL_TREATY_DECISIONS



#include "DecisionsFile.h"



namespace HoI4
{

class NavalTreatyDecisions: public DecisionsFile
{
	public:
		void updateDecisions(const std::set<std::string>& majorIdeologies);
};

}



#endif // NAVAL_TREATY_DECISIONS