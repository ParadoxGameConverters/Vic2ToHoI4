#ifndef EXILED_GOVERNMENTS_DECISONS
#define EXILED_GOVERNMENTS_DECISONS



#include "DecisionsFile.h"



namespace HoI4
{

class ExiledGovernmentsDecisions: public DecisionsFile
{
	public:
		void updateDecisions(const std::set<std::string>& majorIdeologies);
};

}



#endif // EXILED_GOVERNMENTS_DECISONS