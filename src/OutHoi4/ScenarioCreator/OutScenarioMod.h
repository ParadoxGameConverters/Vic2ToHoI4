#ifndef OUT_SCENARIO_MOD_H
#define OUT_SCENARIO_MOD_H



#include "src/HOI4World/ScenarioCreator/Roles/ScenarioMod.h"
#include <string>


namespace HoI4
{

void OutputScenarioMod(const ScenarioMod& mod, std::string output_name);

}


#endif // OUT_SCENARIO_MOD_H