#ifndef GENERIC_DECISIONS_H
#define GENERIC_DECISIONS_H



#include "DecisionsFile.h"
#include <map>
#include <set>
#include <string>



namespace HoI4
{

class GenericDecisions: public DecisionsFile
{
	public:
		void updateDecisions(
			const std::map<int, int>& provinceToStateIdMap,
			const std::set<std::string>& majorIdeologies
		);
};

}



#endif // GENERIC_DECISIONS_H