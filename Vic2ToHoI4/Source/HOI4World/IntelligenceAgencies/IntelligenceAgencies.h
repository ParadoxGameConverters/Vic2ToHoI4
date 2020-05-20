#ifndef INTELLIGENCE_AGENCIES_H
#define INTELLIGENCE_AGENCIES_H



#include "IntelligenceAgency.h"
#include <vector>



namespace HoI4
{

class IntelligenceAgencies
{
  public:
	const auto& getIntelligenceAgencies() const { return intelligenceAgencies; }

  private:
	std::vector<IntelligenceAgency> intelligenceAgencies{IntelligenceAgency{}};
};

} // namespace HoI4



#endif // INTELLIGENCE_AGENCIES_H