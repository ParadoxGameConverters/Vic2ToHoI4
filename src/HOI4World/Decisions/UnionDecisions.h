#ifndef UNION_DECISIONS
#define UNION_DECISIONS



#include "src/HOI4World/Countries/UnionCountry.h"
#include "src/HOI4World/Decisions/DecisionsFile.h"
#include "src/HOI4World/Decisions/DecisionsCategories.h"



namespace HoI4
{

class UnionDecisions: public DecisionsFile
{
  public:
	void createDecisions(const std::vector<HoI4::UnionCountry>& unionCountries);
};

} // namespace HoI4



#endif // UNION_DECISIONS
