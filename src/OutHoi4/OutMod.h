#ifndef OUT_MOD_H
#define OUT_MOD_H



#include "src/HOI4World/HoI4World.h"



void clearOutputFolder(const std::string& outputName);
void output(const HoI4::World& destWorld,
	 const std::string& outputName,
	 bool debugEnabled,
	 const Mods& vic2Mods,
	 const Configuration& theConfiguration);



#endif // OUT_MOD_H