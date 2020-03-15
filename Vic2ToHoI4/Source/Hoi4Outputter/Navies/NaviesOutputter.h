#ifndef NAVIES_OUTPUTTER
#define NAVIES_OUTPUTTER



#include "../../HOI4World/Navies/Navies.h"
#include <ostream>



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



#endif // NAVIES_OUTPUTTER