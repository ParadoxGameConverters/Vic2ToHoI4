#ifndef OUT_TECHNOLOGIES_H
#define OUT_TECHNOLOGIES_H



#include "src/HOI4World/Technologies.h"



namespace HoI4
{

void outputTechnology(const technologies& theTechnologies, std::ostream& output);
void outputResearchBonuses(const technologies& theTechnologies, std::ostream& output);

} // namespace HoI4



#endif // OUT_TECHNOLOGIES_H