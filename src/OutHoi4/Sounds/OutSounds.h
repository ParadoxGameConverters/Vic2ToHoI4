#ifndef OUT_SOUNDS_H
#define OUT_SOUNDS_H



#include "src/HOI4World/Sounds/SoundEffect.h"
#include <string>
#include <vector>



namespace HoI4
{

void outputSounds(const std::filesystem::path& outputName, const std::vector<SoundEffect>& soundEffects);

} // namespace HoI4



#endif // OUT_SOUNDS_H