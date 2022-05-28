#ifndef OUT_DIFFICULTY_SETTINGS
#define OUT_DIFFICULTY_SETTINGS



#include "HOI4World/HoI4Country.h"



namespace HoI4
{

void outputDifficultySettings(const std::vector<std::shared_ptr<Country>>& greatPowers, const std::string& outputName);

}



#endif // OUT_DIFFICULTY_SETTINGS