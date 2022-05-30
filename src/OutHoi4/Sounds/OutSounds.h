#ifndef OUT_SOUNDS_H
#define OUT_SOUNDS_H



#include "HOI4World/Sounds/SoundEffect.h"
#include <string>
#include <vector>



namespace HoI4
{

void outputSounds(const std::string& outputName, const std::vector<SoundEffect>& soundEffects);

} // namespace HoI4



#endif // OUT_SOUNDS_H