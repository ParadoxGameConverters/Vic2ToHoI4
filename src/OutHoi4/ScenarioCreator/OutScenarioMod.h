#ifndef OUT_SCENARIO_MOD_H
#define OUT_SCENARIO_MOD_H



#include "src/HOI4World/ScenarioCreator/Roles/ScenarioMod.h"
#include <string>


namespace HoI4
{

void outputScenarioMod(const ScenarioMod& mod, std::string& outputName);

}


#endif // OUT_SCENARIO_MOD_H