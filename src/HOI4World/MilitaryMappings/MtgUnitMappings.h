#ifndef MTG_UNIT_MAPPINGS_H
#define MTG_UNIT_MAPPINGS_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/MilitaryMappings/HoI4UnitType.h"
#include <map>



namespace HoI4
{

class MtgUnitMappings: commonItems::parser
{
  public:
	explicit MtgUnitMappings(std::istream& theStream);

	[[nodiscard]] bool hasMatchingType(const std::string& Vic2Type) const;
	[[nodiscard]] std::vector<HoI4UnitType> getMatchingUnitInfo(const std::string& Vic2Type) const;

  private:
	std::map<std::string, std::vector<HoI4UnitType>> unitMaps;
};

} // namespace HoI4



#endif // MTG_UNIT_MAPPINGS_H