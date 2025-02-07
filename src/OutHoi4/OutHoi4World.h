#ifndef OUT_HOI4_WORLD_H
#define OUT_HOI4_WORLD_H



#include "src/HOI4World/HoI4World.h"



namespace HoI4
{

void OutputWorld(const World& world,
	 const std::filesystem::path& outputName,
	 bool debugEnabled,
	 const Configuration& theConfiguration);

}



#endif // OUT_HOI4_WORLD_H