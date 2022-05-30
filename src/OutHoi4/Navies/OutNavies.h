#ifndef OUT_NAVIES_H
#define OUT_NAVIES_H



#include "HOI4World/Navies/Navies.h"



namespace HoI4
{

void outputLegacyNavies(const Navies& navies,
	 const technologies& technologies,
	 std::string_view tag,
	 std::ostream& output);
void outputMtgNavies(const Navies& navies,
	 const technologies& technologies,
	 std::string_view tag,
	 std::ostream& output);

} // namespace HoI4



#endif // OUT_NAVIES_H