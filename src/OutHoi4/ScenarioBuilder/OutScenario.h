#ifndef OUT_SCENARIO_H
#define OUT_SCENARIO_H



#include "src/HOI4World/ScenarioBuilder/ScenarioBuilder.h"
#include <ostream>


namespace HoI4
{

void outputScenario(const ScenarioBuilder& scenario, std::string& outputName, std::string& saveName);

}


#endif // OUT_SCENARIO_H