#ifndef OUT_LOCALISATION_H
#define OUT_LOCALISATION_H



#include "src/HOI4World/HoI4Localisation.h"



namespace HoI4
{

void outputLocalisation(const Localisation& localisation, const std::filesystem::path& outputName);

} // namespace HoI4



#endif // OUT_LOCALISATION_H