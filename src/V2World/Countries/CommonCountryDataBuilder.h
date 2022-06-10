#ifndef COMMON_COUNTRY_DATA_BUILDER_H
#define COMMON_COUNTRY_DATA_BUILDER_H



#include "src/V2World/Countries/CommonCountryData.h"
#include <memory>



namespace Vic2
{

class CommonCountryData::Builder
{
  public:
	Builder() { commonCountryData = std::make_unique<CommonCountryData>(); }
	std::unique_ptr<CommonCountryData> Build() { return std::move(commonCountryData); }

	Builder& setColor(commonItems::Color color)
	{
		commonCountryData->theColor = color;
		return *this;
	}

	Builder& addUnitNames(std::string unitType, std::vector<std::string> names)
	{
		commonCountryData->unitNames.insert(std::make_pair(unitType, names));
		return *this;
	}

	Builder& addParty(Party party)
	{
		commonCountryData->parties.push_back(party);
		return *this;
	}

  private:
	std::unique_ptr<CommonCountryData> commonCountryData;
};

} // namespace Vic2



#endif // COMMON_COUNTRY_DATA_BUILDER_H