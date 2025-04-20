#ifndef OUT_INTELLIGENCE_AGENCIES_H
#define OUT_INTELLIGENCE_AGENCIES_H



#include "src/HOI4World/IntelligenceAgencies/IntelligenceAgencies.h"
#include <string>



namespace HoI4
{

void outputIntelligenceAgencies(const IntelligenceAgencies& intelligenceAgencies,
	 const std::filesystem::path& outputName);

} // namespace HoI4



#endif // OUT_INTELLIGENCE_AGENCIES_H