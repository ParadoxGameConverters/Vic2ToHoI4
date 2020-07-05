#ifndef OUT_MOD_H
#define OUT_MOD_H



#include "../HOI4World/HoI4World.h"



void clearOutputFolder(const std::string& outputName);
void output(const HoI4::World& destWorld,
	 const std::string& outputName,
	 bool debugEnabled,
	 const std::vector<std::string>& vic2Mods,
	 const std::string& vic2ModPath,
	 const Configuration& theConfiguration);



#endif // OUT_MOD_H