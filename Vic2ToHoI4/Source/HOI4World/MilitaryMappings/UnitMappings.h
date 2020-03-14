#ifndef UNIT_MAPPINGS_H
#define UNIT_MAPPINGS_H



#include "HoI4UnitType.h"
#include "newParser.h"
#include <map>
#include <vector>



namespace HoI4
{

class UnitMappings: commonItems::parser
{
	public:
		explicit UnitMappings(std::istream& theStream);

		[[nodiscard]] bool hasMatchingType(const std::string& Vic2Type) const;
		[[nodiscard]] std::vector<HoI4UnitType> getMatchingUnitInfo(const std::string& Vic2Type) const;

	private:
		std::map<std::string, std::vector<HoI4UnitType>> unitMap;
};

}



#endif // UNIT_MAPPINGS_H