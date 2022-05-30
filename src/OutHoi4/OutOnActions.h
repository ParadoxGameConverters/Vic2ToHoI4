#ifndef OUT_ON_ACTIONS_H
#define OUT_ON_ACTIONS_H



#include "Configuration.h"
#include "HOI4World/OnActions.h"
#include <set>



namespace HoI4
{

void outputOnActions(const OnActions& onActions,
	 const std::set<std::string>& majorIdeologies,
	 const std::string& outputName);

}



#endif // OUT_ON_ACTIONS_H