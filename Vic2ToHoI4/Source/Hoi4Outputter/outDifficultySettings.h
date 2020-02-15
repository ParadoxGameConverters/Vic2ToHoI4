#ifndef OUT_DIFFICULTY_SETTINGS
#define OUT_DIFFICULTY_SETTINGS

#include "../Configuration.h"
#include "../HOI4World/HoI4Country.h"

namespace HoI4

{


void outputDifficultySettings(
	const std::vector<std::shared_ptr<HoI4::Country>>& greatPowers,
	const Configuration& theConfiguration
);


	
}



#endif //OUT_DIFFICULTY_SETTINGS