#ifndef OUT_MOD_H
#define OUT_MOD_H



#include "../HOI4World/HoI4World.h"



void clearOutputFolder(const std::string& outputName);
void output(HoI4::World& destWorld, const std::string& outputName, bool debugEnabled);



#endif // OUT_MOD_H