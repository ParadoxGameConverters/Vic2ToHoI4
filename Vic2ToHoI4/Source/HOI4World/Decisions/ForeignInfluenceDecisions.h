#ifndef FOREIGN_INFLUENCE_DECISIONS
#define FOREIGN_INFLUENCE_DECISIONS



#include "DecisionsFile.h"



namespace HoI4
{

class ForeignInfluenceDecisions: public DecisionsFile
{
	public:
		void updateDecisions(const std::set<std::string>& majorIdeologies);
};

}



#endif // FOREIGN_INFLUENCE_DECISIONS