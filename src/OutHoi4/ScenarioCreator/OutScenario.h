#ifndef OUT_SCENARIO_H
#define OUT_SCENARIO_H



#include "src/HOI4World/ScenarioCreator/ScenarioCreator.h"


namespace HoI4
{

void outputScenario(const ScenarioCreator& scenario, std::string& outputName, std::string& saveName);

}


#endif // OUT_SCENARIO_H