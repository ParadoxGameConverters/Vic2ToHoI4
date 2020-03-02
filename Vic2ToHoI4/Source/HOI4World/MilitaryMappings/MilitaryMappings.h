#ifndef MILITARY_MAPPINGS
#define MILITARY_MAPPINGS



#include "../Military/DivisionTemplate.h"
#include "MtgUnitMappings.h"
#include "UnitMappings.h"
#include "newParser.h"
#include <map>
#include <memory>
#include <string>
#include <vector>



namespace HoI4
{


class militaryMappings: commonItems::parser
{
  public:
	militaryMappings(std::string name, std::istream& theStream);

	[[nodiscard]] auto getMappingsName() const { return mappingsName; }
	[[nodiscard]] auto& getUnitMappings() const { return *unitMappings; }
	[[nodiscard]] auto& getMtgUnitMappings() const { return *mtgUnitMappings; }
	[[nodiscard]] auto getDivisionTemplates() const { return divisionTemplates; }
	[[nodiscard]] auto getSubstitutes() const { return substitutes; }

  private:
	std::string mappingsName = "";
	std::unique_ptr<UnitMappings> unitMappings;
	std::unique_ptr<MtgUnitMappings> mtgUnitMappings;
	std::vector<DivisionTemplateType> divisionTemplates;
	std::map<std::string, std::string> substitutes;
};


} // namespace HoI4



#endif // MILITARY_MAPPINGS