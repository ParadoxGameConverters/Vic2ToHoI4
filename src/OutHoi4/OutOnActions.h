#ifndef OUT_ON_ACTIONS_H
#define OUT_ON_ACTIONS_H



#include "src/Configuration.h"
#include "src/HOI4World/OnActions.h"
#include <set>



namespace HoI4
{

void outputOnActions(const OnActions& onActions,
	 const std::set<std::string>& majorIdeologies,
	 const std::filesystem::path& outputName);

}



#endif // OUT_ON_ACTIONS_H