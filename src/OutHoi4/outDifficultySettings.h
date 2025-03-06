#ifndef OUT_DIFFICULTY_SETTINGS
#define OUT_DIFFICULTY_SETTINGS



#include "src/HOI4World/HoI4Country.h"



namespace HoI4
{

void outputDifficultySettings(const std::vector<std::shared_ptr<Country>>& greatPowers,
	 const std::filesystem::path& outputName);

} // namespace HoI4



#endif // OUT_DIFFICULTY_SETTINGS