#ifndef INTELLIGENCE_AGENCIES_H
#define INTELLIGENCE_AGENCIES_H



#include "src/HOI4World/HoI4Country.h"
#include "src/HOI4World/Names/Names.h"
#include "src/HOI4World/IntelligenceAgencies/IntelligenceAgency.h"
#include <map>
#include <memory>
#include <vector>



namespace HoI4
{

class IntelligenceAgencies
{
  public:
	class Factory;
	explicit IntelligenceAgencies(std::vector<IntelligenceAgency>&& intelligenceAgencies):
		 intelligenceAgencies(intelligenceAgencies)
	{
	}

	[[nodiscard]] const auto& getIntelligenceAgencies() const { return intelligenceAgencies; }

  private:
	std::vector<IntelligenceAgency> intelligenceAgencies;
};


class IntelligenceAgencies::Factory
{
  public:
	static std::unique_ptr<IntelligenceAgencies> createIntelligenceAgencies(
		 const std::map<std::string, std::shared_ptr<Country>>& countries,
		 Names& names);
};

} // namespace HoI4



#endif // INTELLIGENCE_AGENCIES_H